# Compiler sans Docker

La voie testée est Docker (voir le [README](README.md)) : l'image `docker/Dockerfile` installe exactement ce qui
suit (`python3` et `python3-pil` ne servent pas au build lui-même, mais aux outils de `tools/` et aux tests). Ces instructions servent à compiler directement sur sa machine. Android et la version navigateur ne se
compilent que par Docker ([docs/PLATEFORMES.md](docs/PLATEFORMES.md), [docs/NAVIGATEUR.md](docs/NAVIGATEUR.md)).

## Windows 10/11 (avec WSL)

Installer WSL avec Ubuntu (`wsl --install -d Ubuntu` dans un terminal administrateur), puis ouvrir Ubuntu et
installer les outils :

```
sudo apt install build-essential git make python3 python3-pil pkg-config libpng-dev g++-mingw-w64-x86-64 binutils-mingw-w64-x86-64
```

Télécharger SDL2 pour MinGW (`SDL2-devel-2.30.9-mingw.tar.gz`, sur les
[releases de SDL](https://github.com/libsdl-org/SDL/releases/tag/release-2.30.9)), l'extraire à la racine du dépôt
et renommer le dossier `SDL2-2.30.9` en `SDL2`. Puis :

```
make winwsl -j$(nproc)
```

On obtient `pokeemeraude64.exe`. Le copier avec `SDL2/x86_64-w64-mingw32/bin/SDL2.dll`, les deux fichiers vont
ensemble. Ajouter `KANTO_DEBUG=1` à la commande `make` pour le menu DEBUG.

## Linux (Ubuntu)

```
sudo apt install build-essential git make python3 python3-pil pkg-config libpng-dev libsdl2-dev
make linux -j$(nproc)
```

On obtient `pokeemeraude64` (x86_64). Pour compiler avec clang plutôt que gcc : `COMPILER=clang`.

## macOS (non testé pour PokemonNative3G)

Hérité de la couche PC d'origine. Installer les outils en ligne de commande de Xcode (`xcode-select --install`) et
[Homebrew](https://brew.sh), puis :

```
brew install make pkg-config libpng sdl2 x86_64-elf-binutils
gmake macos -j$(sysctl -n hw.ncpu)
```

Les données du jeu sont assemblées par l'assembleur GNU de `x86_64-elf-binutils` (celui de clang ne sait pas) ;
`gmake` est le GNU make récent de Homebrew. On obtient `pokeemeraude64`, qui utilise la SDL2 de Homebrew.
