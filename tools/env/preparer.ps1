# PokemonNative3G : prépare l'environnement de test automatisé (rien de tout ça n'est versionné : tools/env/ est
# ignoré par git, sauf ce script et le README). Chaque étape est sautée si elle est déjà faite ; on peut relancer.
#
#   preparer-tests.bat                       tout (la licence du SDK Android est demandée par sdkmanager)
#   preparer-tests.bat -AccepterLicenceAndroid   accepte la licence du SDK Android sans la demander
#   preparer-tests.bat -SansAndroid -SansLinux -SansDocker -SansPython   pour sauter une partie
#
# Contenu (tools/env/) : jdk/ (JDK 17 portable, pour les outils Android), android-sdk/ (adb, émulateur, image
# Android 14 x86_64), avd/ (téléphone virtuel « pn3g »), wsl/ (distribution WSL2 « PN3G-Linux », Ubuntu 24.04 avec
# SDL2 et le son), venv/ (Python : numpy, pillow), dl/ (téléchargements). Images Docker : pn3g-build, pn3g-android.
# Prérequis : Docker Desktop lancé, WSL2, Python 3, et pour l'émulateur la plateforme de l'hyperviseur Windows.
param(
    [switch]$AccepterLicenceAndroid,
    [switch]$SansAndroid,
    [switch]$SansLinux,
    [switch]$SansDocker,
    [switch]$SansPython
)
# Pas « Stop » : en Windows PowerShell 5.1, une ligne sur stderr d'un programme (sdkmanager, wsl, docker) devient une
# erreur fatale dès que la sortie est redirigée ; les échecs sont vérifiés à la main (throw)
$ErrorActionPreference = "Continue"
$ProgressPreference = "SilentlyContinue"   # Invoke-WebRequest est très lent avec la barre de progression
$env:WSL_UTF8 = "1"                        # sortie de wsl.exe en UTF-8 (sinon UTF-16)

$Env = $PSScriptRoot
$Repo = (Resolve-Path (Join-Path $Env "..\..")).Path
$Dl = Join-Path $Env "dl"
New-Item -ItemType Directory -Force $Dl | Out-Null

function Step($text) { Write-Host ""; Write-Host "== $text" -ForegroundColor Cyan }
function Done($text) { Write-Host "   $text" -ForegroundColor Green }

function Download($url, $file) {
    $path = Join-Path $Dl $file
    if (Test-Path $path) { Done "déjà téléchargé : $file"; return $path }
    Write-Host "   téléchargement de $file…"
    & curl.exe -sSL --fail -o "$path.part" $url
    if ($LASTEXITCODE -ne 0) { throw "téléchargement impossible : $url" }
    Move-Item "$path.part" $path
    return $path
}

# --- Docker -------------------------------------------------------------------------------------------------------
if (-not $SansDocker) {
    Step "Images Docker (build Windows, Linux, Android)"
    & docker version --format "{{.Server.Version}}" | Out-Null
    if ($LASTEXITCODE -ne 0) { throw "Docker ne répond pas : lancer Docker Desktop" }
    foreach ($image in @(@("pn3g-build", "docker/Dockerfile"), @("pn3g-android", "docker/Dockerfile.android"))) {
        & docker image inspect $image[0] 2>$null | Out-Null
        if ($LASTEXITCODE -eq 0) { Done "$($image[0]) : déjà là"; continue }
        & docker build -t $image[0] -f (Join-Path $Repo $image[1]) (Join-Path $Repo "docker")
        if ($LASTEXITCODE -ne 0) { throw "docker build $($image[0]) a échoué" }
        Done "$($image[0]) : construite"
    }
}

# --- Python --------------------------------------------------------------------------------------------------------
if (-not $SansPython) {
    Step "Python (venv : numpy, pillow)"
    $venv = Join-Path $Env "venv"
    if (-not (Test-Path (Join-Path $venv "Scripts\python.exe"))) {
        & python -m venv $venv
        if ($LASTEXITCODE -ne 0) { throw "python -m venv a échoué" }
    }
    & (Join-Path $venv "Scripts\python.exe") -m pip install --quiet --upgrade pip numpy pillow
    if ($LASTEXITCODE -ne 0) { throw "pip install a échoué" }
    Done "venv prêt : tools/env/venv"
}

# --- Android -------------------------------------------------------------------------------------------------------
if (-not $SansAndroid) {
    Step "JDK 17 portable (outils Android)"
    $jdk = Join-Path $Env "jdk"
    if (-not (Test-Path (Join-Path $jdk "bin\java.exe"))) {
        $zip = Download "https://api.adoptium.net/v3/binary/latest/17/ga/windows/x64/jdk/hotspot/normal/eclipse" "jdk17.zip"
        $tmp = Join-Path $Env "jdk.tmp"
        Remove-Item -Recurse -Force $tmp -ErrorAction SilentlyContinue
        Expand-Archive $zip $tmp
        Move-Item (Get-ChildItem $tmp -Directory | Select-Object -First 1).FullName $jdk
        Remove-Item -Recurse -Force $tmp
    }
    Done "JDK : $jdk"
    $env:JAVA_HOME = $jdk
    $env:Path = "$jdk\bin;$env:Path"

    Step "SDK Android (adb, émulateur, image Android 14 x86_64)"
    $sdk = Join-Path $Env "android-sdk"
    $env:ANDROID_SDK_ROOT = $sdk
    $env:ANDROID_HOME = $sdk
    $env:ANDROID_AVD_HOME = Join-Path $Env "avd"
    $env:ANDROID_EMULATOR_HOME = Join-Path $Env "avd"
    $env:ANDROID_USER_HOME = Join-Path $Env "avd"
    New-Item -ItemType Directory -Force $env:ANDROID_AVD_HOME | Out-Null
    $tools = Join-Path $sdk "cmdline-tools\latest"
    if (-not (Test-Path (Join-Path $tools "bin\sdkmanager.bat"))) {
        $zip = Download "https://dl.google.com/android/repository/commandlinetools-win-11076708_latest.zip" "cmdline-tools.zip"
        $tmp = Join-Path $Env "cmdline.tmp"
        Remove-Item -Recurse -Force $tmp -ErrorAction SilentlyContinue
        Expand-Archive $zip $tmp
        New-Item -ItemType Directory -Force (Split-Path $tools) | Out-Null
        Move-Item (Join-Path $tmp "cmdline-tools") $tools
        Remove-Item -Recurse -Force $tmp
    }
    $sdkmanager = Join-Path $tools "bin\sdkmanager.bat"
    $avdmanager = Join-Path $tools "bin\avdmanager.bat"
    $image = "system-images;android-34;google_apis;x86_64"
    $packages = "platform-tools emulator `"platforms;android-34`" `"$image`""
    if ($AccepterLicenceAndroid) {
        # Les réponses passent par un fichier : un tube PowerShell n'arrive pas jusqu'à Java à travers le .bat
        $yes = Join-Path $Dl "oui.txt"
        Set-Content -Encoding ascii $yes (@("y") * 40)
        cmd /c "`"$sdkmanager`" --sdk_root=`"$sdk`" --licenses < `"$yes`" > nul"
        cmd /c "`"$sdkmanager`" --sdk_root=`"$sdk`" $packages < `"$yes`""
    } else {
        & $sdkmanager "--sdk_root=$sdk" --licenses   # la licence est demandée ici
        cmd /c "`"$sdkmanager`" --sdk_root=`"$sdk`" $packages"
    }
    # sdkmanager rend 0 même quand il saute des paquets (licence refusée) : on vérifie qu'ils sont là
    foreach ($file in @("platform-tools\adb.exe", "emulator\emulator.exe", "system-images\android-34\google_apis\x86_64\system.img")) {
        if (-not (Test-Path (Join-Path $sdk $file))) { throw "paquet Android manquant ($file) : licence refusée ou téléchargement interrompu" }
    }
    Done "SDK : $sdk"

    Step "Téléphone virtuel « pn3g »"
    $avd = Join-Path $env:ANDROID_AVD_HOME "pn3g.avd"
    if (-not (Test-Path $avd)) {
        "no" | & $avdmanager create avd --name pn3g --package $image --device "pixel_6" --force
        if ($LASTEXITCODE -ne 0) { throw "avdmanager a échoué" }
        $config = Join-Path $avd "config.ini"
        $lines = Get-Content $config | Where-Object { $_ -notmatch "^(hw\.ramSize|disk\.dataPartition\.size|hw\.keyboard|hw\.gpu\.enabled|hw\.gpu\.mode|showDeviceFrame|hw\.gamepad)=" }
        $lines += "hw.ramSize=4096", "disk.dataPartition.size=6G", "hw.keyboard=yes", "hw.gpu.enabled=yes",
                  "hw.gpu.mode=host", "showDeviceFrame=no"
        Set-Content -Encoding ascii $config $lines
    }
    Done "AVD : $avd"

    Step "Accélération de l'émulateur (plateforme de l'hyperviseur Windows)"
    # emulator-check directement : « emulator -accel-check » le relance sans guillemets (chemin avec espace)
    $accel = (& (Join-Path $sdk "emulator\emulator-check.exe") accel 2>&1) -join " "
    if ($accel -match "is installed and usable") { Done "accélération OK : $($accel -replace '^accel:\s*0\s*' -replace '\s*accel$')" }
    else { Write-Host "   ATTENTION : pas d'accélération ($accel). Activer « Plateforme de l'hyperviseur Windows » (fonctionnalités Windows)." }
}

# --- Linux (WSL2) --------------------------------------------------------------------------------------------------
if (-not $SansLinux) {
    Step "Distribution WSL2 « PN3G-Linux » (Ubuntu 24.04, SDL2, son)"
    $distros = (& wsl.exe -l -q) | ForEach-Object { $_.Trim() }
    if ($distros -notcontains "PN3G-Linux") {
        & docker image inspect ubuntu:24.04 2>$null | Out-Null
        if ($LASTEXITCODE -ne 0) { & docker pull ubuntu:24.04 }
        $rootfs = Join-Path $Dl "ubuntu-24.04-rootfs.tar"
        if (-not (Test-Path $rootfs)) {
            & docker rm -f pn3g-wsl-rootfs 2>$null | Out-Null
            & docker create --name pn3g-wsl-rootfs ubuntu:24.04 | Out-Null
            & docker export pn3g-wsl-rootfs -o $rootfs
            & docker rm pn3g-wsl-rootfs | Out-Null
        }
        $wsl = Join-Path $Env "wsl"
        New-Item -ItemType Directory -Force $wsl | Out-Null
        & wsl.exe --import PN3G-Linux $wsl $rootfs --version 2
        if ($LASTEXITCODE -ne 0) { throw "wsl --import a échoué" }
    }
    # xdotool : touches du clavier vers la fenêtre ; kmod + python3-evdev : manette virtuelle (module uinput)
    $packages = "libsdl2-2.0-0 pulseaudio-utils python3 python3-evdev imagemagick x11-utils xdotool kmod"
    & wsl.exe -d PN3G-Linux -u root -- bash -c "export DEBIAN_FRONTEND=noninteractive; apt-get update -qq && apt-get install -y -qq $packages > /dev/null 2>&1 && echo paquets installés"
    if ($LASTEXITCODE -ne 0) { throw "apt-get a échoué dans PN3G-Linux" }
    & wsl.exe -d PN3G-Linux -u root -- bash -c "modprobe uinput 2>/dev/null; ls /dev/uinput >/dev/null 2>&1 && echo 'manette virtuelle : module uinput chargé' || echo 'manette virtuelle : pas de module uinput dans ce noyau WSL'; ls /mnt/wslg >/dev/null 2>&1 && echo 'WSLg : affichage et son disponibles' || echo 'WSLg absent'"
    Done "WSL : PN3G-Linux"
}

Step "Terminé"
Write-Host "   Environnement prêt dans tools/env (voir tools/env/README.md)."
