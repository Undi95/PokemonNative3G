# Environnement de test automatisé

Tout ce qui sert à tester le jeu sans y jouer à la main, hors du banc headless de `test/headless/` : émulateur Android,
Linux en WSL2, Python avec numpy. C'est gros (une dizaine de Go) : rien n'est versionné, sauf ce dossier, le script
`preparer.ps1` et `preparer-tests.bat` à la racine du dépôt.

## Préparer

```
preparer-tests.bat
```

Chaque étape est sautée si elle est déjà faite : on peut relancer après une erreur ou une mise à jour. Options :
`-AccepterLicenceAndroid` (sinon `sdkmanager` demande la licence du SDK Android), `-SansAndroid`, `-SansLinux`,
`-SansDocker`, `-SansPython`.

Prérequis : Docker Desktop lancé, WSL2, Python 3, et pour l'émulateur la plateforme de l'hyperviseur Windows
(`Enable-WindowsOptionalFeature -Online -FeatureName HypervisorPlatform` en administrateur, puis redémarrer ;
`preparer-tests.bat` affiche le résultat de `emulator -accel-check`).

## Contenu de `tools/env/`

| Dossier | Contenu |
|---|---|
| `dl/` | téléchargements (JDK, outils Android, système de fichiers d'Ubuntu exporté de Docker) |
| `jdk/` | JDK 17 portable (Eclipse Temurin), pour `sdkmanager` et `avdmanager` |
| `android-sdk/` | outils Android, `adb` (`platform-tools`), émulateur, image Android 14 x86_64 (Google APIs) |
| `avd/` | téléphone virtuel `pn3g` (Pixel 6, 4 Go de mémoire) et réglages de l'émulateur |
| `wsl/` | disque de la distribution WSL2 `PN3G-Linux` (Ubuntu 24.04 : SDL2, PulseAudio, evdev, xdotool, ImageMagick) |
| `venv/` | Python : numpy (analyse du son), pillow |

Images Docker construites si elles manquent : `pn3g-build` (Windows, Linux, ASan), `pn3g-android` (APK).

## Bancs

Tous pilotent une build DEBUG par la console des outils de debug (`--devtools PORT`, `docs/DEVTOOLS.md`) ; la
commande de console `touches N` dit quelles touches le jeu a vraiment reçues (clavier, manette, écran tactile).

| Banc | Plateforme | Ce qu'il fait |
|---|---|---|
| `test/desktop/run.py` | Windows | vrai exe, touches envoyées à la fenêtre (messages Windows) : touche de reset, hasard et ID dresseur d'un lancement à l'autre |
| `test/desktop/linux_bench.py` | Linux (WSL) | `wsl -d PN3G-Linux -- python3 test/desktop/linux_bench.py` : fenêtre WSLg, son (`parec`), clavier (`xdotool`), manette Xbox 360 virtuelle (`uinput`) |
| `test/android/android.py` | Android | émulateur `pn3g`, APK debug, zones tactiles et plusieurs doigts (`sendevent`), manette HID virtuelle (outil `hid` d'Android : comme une manette Bluetooth) |

Builds à faire avant : `out/winwsl/pokeemeraude64.exe` et `out/linux/pokeemeraude64` avec `KANTO_DEBUG=1`,
`out/android/PokemonNative3G-debug.apk` (`FLAVOR=debugtools`, voir `build-all.sh`).

Bon à savoir :
- l'émulateur réutilise un téléphone déjà lancé ; le premier démarrage (données neuves) prend plusieurs minutes ;
- la fenêtre du jeu sur Android évite l'encoche de la caméra : les zones tactiles sont calculées dans la fenêtre
  (`dumpsys window`), pas dans l'écran ;
- `sendevent` et `hid` passent par `adb root` (image Google APIs, pas Google Play), ce qui coupe la console un instant ;
- sous WSL, pas de udev : SDL scrute `/dev/input` (`SDL_JOYSTICK_DISABLE_UDEV=1`) et `modprobe uinput` est à refaire
  après chaque redémarrage de WSL (le banc le fait).

## Retirer

Supprimer `tools/env/` (sauf ce fichier et `preparer.ps1`), puis `wsl --unregister PN3G-Linux`.
