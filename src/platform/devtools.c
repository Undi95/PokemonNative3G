// PokemonNative3G : ce que la plateforme fournit aux outils de debug (builds KANTO_DEBUG=1), voir
// include/platform/devtools.h et docs/DEVTOOLS.md :
// - les noms des fonctions et des données, lus dans le fichier .syms que docker/build.sh pose à côté du jeu ;
// - la console en direct (--devtools PORT, sur 127.0.0.1) : une commande des outils par ligne, réponse en une ligne
//   de JSON {"reply": "…"} (ou {"reply": …, "error": …}). Le client est test/headless/dev.py.
#if defined(PORTABLE) && defined(KANTO_DEBUG_START)
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

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
#ifdef __ANDROID__
#include <jni.h>
#endif

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

// --- Session (rapport de bug rejouable) -----------------------------------------------------------------------
// Depuis le lancement : la sauvegarde telle qu'au lancement, l'heure locale du lancement et les touches de chaque
// image du jeu (par plages). test/headless/replay.py rejoue tout dans le banc headless jusqu'au rapport.

// La dernière image affichée (VDraw), pour le rapport et la commande « capture » de la console
static const unsigned short *sFrame;

// Les 10 dernières secondes, une image toutes les 30 : ce que le joueur a vu avant d'ouvrir le menu du rapport
#define HISTORY_FRAMES 20
#define HISTORY_INTERVAL 30
static unsigned short sHistory[HISTORY_FRAMES][DISPLAY_WIDTH * DISPLAY_HEIGHT];
static unsigned sHistoryCount, sFramesDrawn;

struct KeyRun
{
    unsigned frames;
    unsigned short keys;
};

static unsigned char *sBootSave;
static long sBootSaveSize;
static char sSavePath[1024];
static char sReportDir[1024];
static struct tm sBootTime;
static struct KeyRun *sKeyRuns;
static unsigned sKeyRunCount, sKeyRunCapacity;
static unsigned long sSessionFrames;

void DevTools_StartSession(const char *savePath, const char *reportDir)
{
    FILE *file = fopen(savePath, "rb");
    time_t now = time(NULL);

    snprintf(sSavePath, sizeof(sSavePath), "%s", savePath);
    snprintf(sReportDir, sizeof(sReportDir), "%s", reportDir);
    sBootTime = *localtime(&now);
    free(sBootSave);
    sBootSave = NULL;
    sBootSaveSize = 0;
    if (file != NULL)
    {
        fseek(file, 0, SEEK_END);
        sBootSaveSize = ftell(file);
        fseek(file, 0, SEEK_SET);
        sBootSave = malloc(sBootSaveSize > 0 ? sBootSaveSize : 1);
        if (sBootSave == NULL || fread(sBootSave, 1, sBootSaveSize, file) != (size_t)sBootSaveSize)
            sBootSaveSize = 0;
        fclose(file);
    }
}

const char *DevTools_GetReportDir(void)
{
    return sReportDir;
}

// Touches appuyées par la console (« touche A+UP 10 ») : ajoutées à celles du joueur pendant tant d'images
static unsigned short sInjectedKeys;
static unsigned sInjectedFrames;

static const struct { unsigned short key; const char *name; } sButtonNames[] = {
    {A_BUTTON, "A"}, {B_BUTTON, "B"}, {SELECT_BUTTON, "SELECT"}, {START_BUTTON, "START"}, {DPAD_RIGHT, "RIGHT"},
    {DPAD_LEFT, "LEFT"}, {DPAD_UP, "UP"}, {DPAD_DOWN, "DOWN"}, {R_BUTTON, "R"}, {L_BUTTON, "L"},
};

unsigned short DevTools_FrameKeys(unsigned short physical)
{
    unsigned short keys = physical;

    if (sInjectedFrames > 0)
    {
        keys |= sInjectedKeys;
        sInjectedFrames--;
    }
    DevTools_RecordFrameKeys(keys);
    return keys;
}

void DevTools_RecordFrameKeys(unsigned short keys)
{
    sSessionFrames++;
    if (sKeyRunCount > 0 && sKeyRuns[sKeyRunCount - 1].keys == keys)
    {
        sKeyRuns[sKeyRunCount - 1].frames++;
        return;
    }
    if (sKeyRunCount == sKeyRunCapacity)
    {
        unsigned capacity = sKeyRunCapacity == 0 ? 4096 : sKeyRunCapacity * 2;
        struct KeyRun *runs = realloc(sKeyRuns, capacity * sizeof(*runs));

        if (runs == NULL)
            return;
        sKeyRuns = runs;
        sKeyRunCapacity = capacity;
    }
    sKeyRuns[sKeyRunCount].frames = 1;
    sKeyRuns[sKeyRunCount++].keys = keys;
}

// --- Rapport de bug : une archive tar (lisible partout, envoyée telle quelle depuis le téléphone) -------------

static void TarWrite(FILE *tar, const char *name, const void *data, unsigned long size)
{
    unsigned char header[512];
    unsigned sum = 0, i;
    static const unsigned char sZeros[512];

    memset(header, 0, sizeof(header));
    snprintf((char *)header, 100, "%s", name);
    snprintf((char *)header + 100, 8, "%07o", 0644);
    snprintf((char *)header + 108, 8, "%07o", 0);
    snprintf((char *)header + 116, 8, "%07o", 0);
    snprintf((char *)header + 124, 12, "%011lo", size);
    snprintf((char *)header + 136, 12, "%011lo", (unsigned long)time(NULL));
    memset(header + 148, ' ', 8);
    header[156] = '0';
    memcpy(header + 257, "ustar", 6);
    memcpy(header + 263, "00", 2);
    for (i = 0; i < sizeof(header); i++)
        sum += header[i];
    snprintf((char *)header + 148, 8, "%06o", sum);
    header[155] = ' ';
    fwrite(header, 1, sizeof(header), tar);
    fwrite(data, 1, size, tar);
    if (size % 512 != 0)
        fwrite(sZeros, 1, 512 - size % 512, tar);
}

// Une image du jeu (ABGR1555) en PPM
static void TarWriteImage(FILE *tar, const char *name, const unsigned short *frame)
{
    char header[32];
    int headerLength = snprintf(header, sizeof(header), "P6\n%d %d\n255\n", DISPLAY_WIDTH, DISPLAY_HEIGHT);
    unsigned long size = headerLength + 3 * DISPLAY_WIDTH * DISPLAY_HEIGHT;
    unsigned char *image = malloc(size);
    int x;

    if (image == NULL)
        return;
    memcpy(image, header, headerLength);
    for (x = 0; x < DISPLAY_WIDTH * DISPLAY_HEIGHT; x++)
    {
        image[headerLength + 3 * x] = (frame[x] & 0x1F) << 3;
        image[headerLength + 3 * x + 1] = ((frame[x] >> 5) & 0x1F) << 3;
        image[headerLength + 3 * x + 2] = ((frame[x] >> 10) & 0x1F) << 3;
    }
    TarWrite(tar, name, image, size);
    free(image);
}

// Un texte qui grandit (le rapport, les touches)
struct Text
{
    char *data;
    unsigned long length, size;
};

static void TextAdd(struct Text *text, const char *format, ...) __attribute__((format(printf, 2, 3)));

static void TextAdd(struct Text *text, const char *format, ...)
{
    va_list args;
    int length;

    for (;;)
    {
        va_start(args, format);
        length = vsnprintf(text->data + text->length, text->size - text->length, format, args);
        va_end(args);
        if (length < 0)
            return;
        if (text->length + length < text->size)
            break;
        text->size = (text->size + length) * 2 + 4096;
        text->data = realloc(text->data, text->size);
        if (text->data == NULL)
        {
            text->size = text->length = 0;
            return;
        }
    }
    text->length += length;
}

static void AddButtons(struct Text *text, unsigned short keys)
{
    bool8 first = TRUE;
    unsigned i;

    for (i = 0; i < ARRAY_COUNT(sButtonNames); i++)
    {
        if (keys & sButtonNames[i].key)
        {
            TextAdd(text, "%s%s", first ? "" : "+", sButtonNames[i].name);
            first = FALSE;
        }
    }
    if (first)
        TextAdd(text, "-");
}

static unsigned char *ReadWholeFile(const char *path, unsigned long *size)
{
    FILE *file = fopen(path, "rb");
    unsigned char *data;

    *size = 0;
    if (file == NULL)
        return NULL;
    fseek(file, 0, SEEK_END);
    *size = ftell(file);
    fseek(file, 0, SEEK_SET);
    data = malloc(*size > 0 ? *size : 1);
    if (data != NULL && fread(data, 1, *size, file) != *size)
        *size = 0;
    fclose(file);
    return data;
}

// Les commandes des outils dont le rapport garde le résultat (l'état du jeu au moment du rapport)
static const char *const sReportCommands[] = {
    "sys.anomalies", "jeu.etat", "jeu.options", "carte.info", "carte.objets", "scripts.contexte", "joueur.equipe",
    "joueur.sac", "combat.etat", "texte.imprimantes", "gfx.fenetres", "gfx.bg", "gfx.sprites", "son.etat", "sys.etat",
};

bool8 DevTools_WriteReport(char *name, unsigned nameSize)
{
    static char sText[32768], sNamed[40000];
    struct Text report = {0}, keys = {0};
    char path[1300];
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    unsigned long saveSize;
    unsigned char *save;
    FILE *tar;
    unsigned i;

    snprintf(name, nameSize, "rapport_%04d-%02d-%02d_%02d-%02d-%02d.tar", local->tm_year + 1900, local->tm_mon + 1,
             local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec);
    snprintf(path, sizeof(path), "%s", sReportDir);
#ifdef _WIN32
    CreateDirectoryA(path, NULL);
#else
    mkdir(path, 0755);
#endif
    snprintf(path, sizeof(path), "%s%s", sReportDir, name);
    tar = fopen(path, "wb");
    if (tar == NULL)
        return FALSE;

    // rapport.txt : quand, puis l'état du jeu par les outils (adresses nommées)
    TextAdd(&report, "Rapport de bug PokemonNative3G (build DEBUG)\n");
    TextAdd(&report, "lancement : %04d-%02d-%02d %02d:%02d:%02d (heure locale)\n", sBootTime.tm_year + 1900,
            sBootTime.tm_mon + 1, sBootTime.tm_mday, sBootTime.tm_hour, sBootTime.tm_min, sBootTime.tm_sec);
    TextAdd(&report, "rapport : %04d-%02d-%02d %02d:%02d:%02d, %lu images depuis le lancement\n", local->tm_year + 1900,
            local->tm_mon + 1, local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec, sSessionFrames);
    for (i = 0; i < ARRAY_COUNT(sReportCommands); i++)
    {
        struct DebugToolsOutput out = {sText, sizeof(sText), 0};

        DebugTools_RunLine(sReportCommands[i], &out);
        DevTools_NameAddresses(sNamed, sText, sizeof(sNamed));
        TextAdd(&report, "\n=== %s\n%s", sReportCommands[i], sNamed);
    }
    TarWrite(tar, "rapport.txt", report.data, report.length);

    // touches.txt : l'entrée du banc headless (test/headless/run.py, replay.py) depuis le lancement
    TextAdd(&keys, "# Touches de chaque image depuis le lancement (entree du banc headless : replay.py)\n");
    TextAdd(&keys, "# lancement %04d-%02d-%02d %02d:%02d:%02d\n", sBootTime.tm_year + 1900, sBootTime.tm_mon + 1,
            sBootTime.tm_mday, sBootTime.tm_hour, sBootTime.tm_min, sBootTime.tm_sec);
    for (i = 0; i < sKeyRunCount; i++)
    {
        TextAdd(&keys, "%u ", sKeyRuns[i].frames);
        AddButtons(&keys, sKeyRuns[i].keys);
        TextAdd(&keys, "\n");
    }
    TarWrite(tar, "touches.txt", keys.data, keys.length);

    // Les sauvegardes : au lancement (point de départ du rejeu) et maintenant
    TarWrite(tar, "lancement.sav", sBootSave != NULL ? sBootSave : (const unsigned char *)"", sBootSaveSize);
    save = ReadWholeFile(sSavePath, &saveSize);
    TarWrite(tar, "maintenant.sav", save != NULL ? save : (const unsigned char *)"", saveSize);
    free(save);

    // capture.ppm : la dernière image ; avant_NN.ppm : les 10 secondes d'avant (00 = la plus ancienne)
    if (sFrame != NULL)
    {
        unsigned first = sHistoryCount > HISTORY_FRAMES ? sHistoryCount - HISTORY_FRAMES : 0;

        TarWriteImage(tar, "capture.ppm", sFrame);
        for (i = first; i < sHistoryCount; i++)
        {
            char imageName[32];

            snprintf(imageName, sizeof(imageName), "avant_%02u.ppm", i - first);
            TarWriteImage(tar, imageName, sHistory[i % HISTORY_FRAMES]);
        }
    }

    // Fin de l'archive : deux blocs vides
    {
        static const unsigned char sEnd[1024];

        fwrite(sEnd, 1, sizeof(sEnd), tar);
    }
    fclose(tar);
    free(report.data);
    free(keys.data);
#ifdef __ANDROID__
    // L'APK propose de l'envoyer (GameActivity.shareReport, ReportProvider)
    {
        JNIEnv *env = SDL_AndroidGetJNIEnv();
        jobject activity = SDL_AndroidGetActivity();

        if (env != NULL && activity != NULL)
        {
            jclass activityClass = (*env)->GetObjectClass(env, activity);
            jmethodID share = (*env)->GetStaticMethodID(env, activityClass, "shareReport", "(Ljava/lang/String;)V");

            if (share != NULL)
            {
                jstring jpath = (*env)->NewStringUTF(env, path);

                (*env)->CallStaticVoidMethod(env, activityClass, share, jpath);
                (*env)->DeleteLocalRef(env, jpath);
            }
            if ((*env)->ExceptionCheck(env))
                (*env)->ExceptionClear(env);
            (*env)->DeleteLocalRef(env, activityClass);
            (*env)->DeleteLocalRef(env, activity);
        }
    }
#endif
    return TRUE;
}

// --- Console en direct ----------------------------------------------------------------------------------------

static Socket sServer = NO_SOCKET, sClient = NO_SOCKET;
static char sLine[1024];
static unsigned sLineLength;

void DevTools_SetFrame(const unsigned short *image)
{
    sFrame = image;
    if (sFramesDrawn++ % HISTORY_INTERVAL == 0)
        memcpy(sHistory[sHistoryCount++ % HISTORY_FRAMES], image, sizeof(sHistory[0]));
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

    // « touche A+UP 10 » : ces boutons, en plus de ceux du joueur, pendant 10 images (2 par défaut)
    if (strncmp(line, "touche ", 7) == 0)
    {
        char names[64], *name;
        unsigned frames = 2, i;

        sInjectedKeys = 0;
        if (sscanf(line + 7, "%63s %u", names, &frames) >= 1)
        {
            for (name = strtok(names, "+"); name != NULL; name = strtok(NULL, "+"))
            {
                for (i = 0; i < ARRAY_COUNT(sButtonNames); i++)
                {
                    if (strcmp(name, sButtonNames[i].name) == 0)
                        sInjectedKeys |= sButtonNames[i].key;
                }
            }
        }
        sInjectedFrames = sInjectedKeys != 0 ? frames : 0;
        Send(sInjectedKeys != 0 ? "{\"reply\": 1}\n" : "{\"reply\": 0, \"error\": \"bouton inconnu\"}\n");
        return;
    }
    if (strncmp(line, "capture ", 8) == 0)
    {
        ok = WriteCapture(line + 8);
        Send(ok ? "{\"reply\": 1}\n" : "{\"reply\": 0, \"error\": \"capture impossible\"}\n");
        return;
    }
    // « touches N » : les N dernières plages de touches reçues par le jeu, clavier, manette, écran tactile et console
    // confondus (bancs : test/android/android.py, test/desktop/). 1re ligne « image I » (images depuis le lancement),
    // puis « DÉBUT IMAGES BOUTONS » par plage, la plus récente en dernier
    if (strncmp(line, "touches", 7) == 0 && (line[7] == '\0' || line[7] == ' '))
    {
        struct Text keys = {0};
        unsigned count = 20, first, i;
        unsigned long start = sSessionFrames;

        sscanf(line + 7, "%u", &count);
        first = sKeyRunCount > count ? sKeyRunCount - count : 0;
        for (i = first; i < sKeyRunCount; i++)
            start -= sKeyRuns[i].frames;
        TextAdd(&keys, "image %lu\n", sSessionFrames);
        for (i = first; i < sKeyRunCount; i++)
        {
            TextAdd(&keys, "%lu %u ", start, sKeyRuns[i].frames);
            AddButtons(&keys, sKeyRuns[i].keys);
            TextAdd(&keys, "\n");
            start += sKeyRuns[i].frames;
        }
        Send("{\"reply\": ");
        SendJsonString(keys.data != NULL ? keys.data : "");
        Send("}\n");
        free(keys.data);
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
