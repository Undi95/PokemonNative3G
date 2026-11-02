// PokemonNative3G : ce que la plateforme fournit aux outils de debug (builds KANTO_DEBUG=1), voir
// include/platform/devtools.h et docs/DEVTOOLS.md :
// - les noms des fonctions et des données, lus dans le fichier .syms que docker/build.sh pose à côté du jeu ;
// - la console en direct (--devtools PORT, sur 127.0.0.1) : une commande des outils par ligne, réponse en une ligne
//   de JSON {"reply": "…"} (ou {"reply": …, "error": …}). Le client est test/headless/dev.py.
#if defined(PORTABLE) && defined(KANTO_DEBUG_START)
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define NOMINMAX // global.h has its own
#include <winsock2.h>
typedef SOCKET Socket;
#define NO_SOCKET INVALID_SOCKET
#define CloseSocket closesocket
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
typedef int Socket;
#define NO_SOCKET (-1)
#define CloseSocket close
#endif

#include <SDL2/SDL.h>

#include "global.h"
#include "debug_tools.h"
#include "platform/devtools.h"

// --- Symboles -------------------------------------------------------------------------------------------------

struct Symbol
{
    long long offset;
    char *name;
};

static struct Symbol *sSymbols;
static int sSymbolCount = -1; // -1 : pas encore lu

static int CompareSymbols(const void *a, const void *b)
{
    long long x = ((const struct Symbol *)a)->offset, y = ((const struct Symbol *)b)->offset;

    return x < y ? -1 : x > y;
}

static SDL_RWops *OpenSymbols(void)
{
    static const char *const sNames[] = {"pokeemeraude64.syms", "PokemonNative3G.syms"};
    char *base = SDL_GetBasePath();
    SDL_RWops *file = NULL;
    char path[1024];
    unsigned i;

    for (i = 0; i < ARRAY_COUNT(sNames) && file == NULL; i++)
    {
        if (base != NULL)
        {
            snprintf(path, sizeof(path), "%s%s", base, sNames[i]);
            file = SDL_RWFromFile(path, "rb");
        }
        // Sur Android : dans les assets de l'APK
        if (file == NULL)
            file = SDL_RWFromFile(sNames[i], "rb");
    }
    SDL_free(base);
    return file;
}

static void LoadSymbols(void)
{
    SDL_RWops *file = OpenSymbols();
    Sint64 size;
    char *text, *line;
    unsigned long long agbMain = 0;
    int capacity = 0, i;

    sSymbolCount = 0;
    if (file == NULL)
        return;
    size = SDL_RWsize(file);
    text = malloc(size + 1);
    if (text == NULL || SDL_RWread(file, text, 1, size) != (size_t)size)
    {
        free(text);
        SDL_RWclose(file);
        return;
    }
    SDL_RWclose(file);
    text[size] = '\0';

    // « adresse type nom », une ligne par symbole (nm)
    for (line = strtok(text, "\r\n"); line != NULL; line = strtok(NULL, "\r\n"))
    {
        unsigned long long address;
        char type, name[256];

        if (sscanf(line, "%llx %c %255s", &address, &type, name) != 3 || name[0] == '.')
            continue;
        if (sSymbolCount == capacity)
        {
            capacity = capacity == 0 ? 4096 : capacity * 2;
            sSymbols = realloc(sSymbols, capacity * sizeof(*sSymbols));
        }
        sSymbols[sSymbolCount].offset = (long long)address;
        sSymbols[sSymbolCount].name = strdup(name);
        if (strcmp(name, "AgbMain") == 0)
            agbMain = address;
        sSymbolCount++;
    }
    free(text);
    for (i = 0; i < sSymbolCount; i++)
        sSymbols[i].offset -= (long long)agbMain;
    qsort(sSymbols, sSymbolCount, sizeof(*sSymbols), CompareSymbols);
}

const char *DevTools_SymbolName(long long offset, long long *delta)
{
    int low = 0, high;

    if (sSymbolCount < 0)
        LoadSymbols();
    high = sSymbolCount - 1;
    if (high < 0 || offset < sSymbols[0].offset)
        return NULL;
    // Le dernier symbole à l'adresse ou avant
    while (low < high)
    {
        int middle = (low + high + 1) / 2;

        if (sSymbols[middle].offset <= offset)
            low = middle;
        else
            high = middle - 1;
    }
    *delta = offset - sSymbols[low].offset;
    return sSymbols[low].name;
}

void DevTools_NameAddresses(char *dest, const char *src, unsigned destSize)
{
    unsigned n = 0;

    while (*src != '\0' && n + 1 < destSize)
    {
        char *end;
        long long offset, delta;
        const char *name;

        if (*src != '@')
        {
            dest[n++] = *src++;
            continue;
        }
        offset = strtoll(src + 1, &end, 10);
        if (end == src + 1)
        {
            dest[n++] = *src++;
            continue;
        }
        src = end;
        name = offset == 0 ? "NULL" : DevTools_SymbolName(offset, &delta);
        if (name == NULL)
            n += snprintf(dest + n, destSize - n, "?%lld", offset);
        else if (offset != 0 && delta != 0)
            n += snprintf(dest + n, destSize - n, "%s+%#llx", name, delta);
        else
            n += snprintf(dest + n, destSize - n, "%s", name);
        if (n >= destSize)
            n = destSize - 1;
    }
    dest[n] = '\0';
}

// --- Console en direct ----------------------------------------------------------------------------------------

static Socket sServer = NO_SOCKET, sClient = NO_SOCKET;
static char sLine[1024];
static unsigned sLineLength;
static const unsigned short *sFrame;

void DevTools_SetFrame(const unsigned short *image)
{
    sFrame = image;
}

void DevTools_StartConsole(int port)
{
    struct sockaddr_in address;
    int yes = 1;

#ifdef _WIN32
    WSADATA data;

    if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
        return;
#endif
    sServer = socket(AF_INET, SOCK_STREAM, 0);
    if (sServer == NO_SOCKET)
        return;
    setsockopt(sServer, SOL_SOCKET, SO_REUSEADDR, (const char *)&yes, sizeof(yes));
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if (bind(sServer, (struct sockaddr *)&address, sizeof(address)) != 0 || listen(sServer, 1) != 0)
    {
        fprintf(stderr, "Console de debug : le port %d est pris\n", port);
        CloseSocket(sServer);
        sServer = NO_SOCKET;
        return;
    }
    printf("Console de debug : 127.0.0.1:%d (test/headless/dev.py)\n", port);
}

static bool8 IsReadable(Socket socket)
{
    fd_set set;
    struct timeval wait = {0, 0};

    FD_ZERO(&set);
    FD_SET(socket, &set);
    return select((int)socket + 1, &set, NULL, NULL, &wait) > 0;
}

static void Send(const char *text)
{
    size_t length = strlen(text);

    while (length > 0)
    {
        int sent = send(sClient, text, (int)length, 0);

        if (sent <= 0)
            return;
        text += sent;
        length -= sent;
    }
}

static void SendJsonString(const char *text)
{
    char chunk[512];
    unsigned n = 0;

    Send("\"");
    for (; *text != '\0'; text++)
    {
        if (n + 8 > sizeof(chunk))
        {
            chunk[n] = '\0';
            Send(chunk);
            n = 0;
        }
        if (*text == '"' || *text == '\\')
        {
            chunk[n++] = '\\';
            chunk[n++] = *text;
        }
        else if (*text == '\n')
        {
            chunk[n++] = '\\';
            chunk[n++] = 'n';
        }
        else if ((unsigned char)*text < 0x20)
        {
            n += snprintf(chunk + n, sizeof(chunk) - n, "\\u%04x", (unsigned char)*text);
        }
        else
        {
            chunk[n++] = *text;
        }
    }
    chunk[n] = '\0';
    Send(chunk);
    Send("\"");
}

// « capture CHEMIN » : la dernière image en PPM
static bool8 WriteCapture(const char *path)
{
    FILE *file;
    int i;

    if (sFrame == NULL || (file = fopen(path, "wb")) == NULL)
        return FALSE;
    fprintf(file, "P6\n%d %d\n255\n", DISPLAY_WIDTH, DISPLAY_HEIGHT);
    for (i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; i++)
    {
        unsigned char rgb[3] = {(sFrame[i] & 0x1F) << 3, ((sFrame[i] >> 5) & 0x1F) << 3, ((sFrame[i] >> 10) & 0x1F) << 3};

        fwrite(rgb, 1, sizeof(rgb), file);
    }
    fclose(file);
    return TRUE;
}

static void HandleLine(const char *line)
{
    static char sText[32768], sNamed[40000];
    struct DebugToolsOutput out = {sText, sizeof(sText), 0};
    bool8 ok;

    if (strncmp(line, "capture ", 8) == 0)
    {
        ok = WriteCapture(line + 8);
        Send(ok ? "{\"reply\": 1}\n" : "{\"reply\": 0, \"error\": \"capture impossible\"}\n");
        return;
    }
    ok = DebugTools_RunLine(line, &out);
    DevTools_NameAddresses(sNamed, sText, sizeof(sNamed));
    Send("{\"reply\": ");
    SendJsonString(sNamed);
    Send(ok ? "}\n" : ", \"error\": \"commande refusee\"}\n");
}

void DevTools_PollConsole(void)
{
    if (sServer == NO_SOCKET)
        return;
    if (sClient == NO_SOCKET)
    {
        if (!IsReadable(sServer))
            return;
        sClient = accept(sServer, NULL, NULL);
        sLineLength = 0;
        if (sClient == NO_SOCKET)
            return;
    }
    while (sClient != NO_SOCKET && IsReadable(sClient))
    {
        char c;
        int received = recv(sClient, &c, 1, 0);

        if (received <= 0)
        {
            CloseSocket(sClient);
            sClient = NO_SOCKET;
            return;
        }
        if (c == '\n' || sLineLength + 1 >= sizeof(sLine))
        {
            sLine[sLineLength] = '\0';
            if (sLineLength > 0 && sLine[sLineLength - 1] == '\r')
                sLine[sLineLength - 1] = '\0';
            sLineLength = 0;
            HandleLine(sLine);
        }
        else
        {
            sLine[sLineLength++] = c;
        }
    }
}

#endif // PORTABLE && KANTO_DEBUG_START
