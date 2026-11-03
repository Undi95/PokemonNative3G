@echo off
rem PokemonNative3G : prépare l'environnement de test automatisé dans tools\env (non versionné).
rem Options : -AccepterLicenceAndroid -SansAndroid -SansLinux -SansDocker -SansPython (voir tools\env\preparer.ps1)
chcp 65001 >nul
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0tools\env\preparer.ps1" %*
if errorlevel 1 (
    echo.
    echo La preparation a echoue : voir le message ci-dessus.
    pause
    exit /b 1
)
