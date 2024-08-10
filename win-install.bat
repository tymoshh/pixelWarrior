@echo off
setlocal enabledelayedexpansion


echo PIXEL WARRIOR INSTALLER
echo(
pause



rem downloading game executable

curl https://raw.githubusercontent.com/tymoshh/pixelWarrior/main/pixelWarrior.exe -o pixelWarrior.exe
echo



rem creating and downloading res folder
mkdir res
cd res

curl https://raw.githubusercontent.com/tymoshh/pixelWarrior/main/res/AK47.png -o AK47.png
curl https://raw.githubusercontent.com/tymoshh/pixelWarrior/main/res/background.png -o background.png
curl https://raw.githubusercontent.com/tymoshh/pixelWarrior/main/res/bullet.png -o bullet.png
curl https://raw.githubusercontent.com/tymoshh/pixelWarrior/main/res/hero.png -o hero.png
curl https://raw.githubusercontent.com/tymoshh/pixelWarrior/main/res/tower.png -o tower.png
curl https://raw.githubusercontent.com/tymoshh/pixelWarrior/main/res/zombie.png -o zombie.png

curl https://raw.githubusercontent.com/tymoshh/pixelWarrior/main/res/EricSkiff_Underclocked.wav -o EricSkiff_Underclocked.wav
curl https://raw.githubusercontent.com/tymoshh/pixelWarrior/main/res/gunUpgradeFailSound.wav -o gunUpgradeFailSound.wav
curl https://raw.githubusercontent.com/tymoshh/pixelWarrior/main/res/gunUpgradeSound.wav -o gunUpgradeSound.wav
curl https://raw.githubusercontent.com/tymoshh/pixelWarrior/main/res/shootSound.wav -o shootSound.wav

curl https://raw.githubusercontent.com/tymoshh/pixelWarrior/main/res/ThaleahFat.ttf -o ThaleahFat.ttf

cd ..


rem downloading sdl2 libraries which can give us the binaries

mkdir bins

curl -L -o SDL2.tar.gz https://github.com/libsdl-org/SDL/releases/download/release-2.30.5/SDL2-devel-2.30.5-mingw.tar.gz
tar -xvzf SDL2.tar.gz
for /d %%i in (SDL2*) do (
  set "folderName=%%~nxi"
)
xcopy "!folderName!\x86_64-w64-mingw32\bin\SDL2.dll" "%cd%\bins\" /e
rd /s /q "!folderName!"
del SDL2.tar.gz

curl -L -o SDL2_image.tar.gz https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.2/SDL2_image-devel-2.8.2-mingw.tar.gz
tar -xvzf SDL2_image.tar.gz
for /d %%i in (SDL2*) do (
  set "folderName=%%~nxi"
)
xcopy "!folderName!\x86_64-w64-mingw32\bin\SDL2_image.dll" "%cd%\bins\" /e
rd /s /q "!folderName!"
del SDL2_image.tar.gz

curl -L -o SDL2_mixer.tar.gz https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.0/SDL2_mixer-devel-2.8.0-mingw.tar.gz
tar -xvzf SDL2_mixer.tar.gz
for /d %%i in (SDL2*) do (
  set "folderName=%%~nxi"
)
xcopy "!folderName!\x86_64-w64-mingw32\bin\SDL2_mixer.dll" "%cd%\bins\" /e
rd /s /q "!folderName!"
del SDL2_mixer.tar.gz

curl -L -o SDL2_ttf.tar.gz https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.22.0/SDL2_ttf-devel-2.22.0-mingw.tar.gz
tar -xvzf SDL2_ttf.tar.gz
for /d %%i in (SDL2*) do (
  set "folderName=%%~nxi"
)
xcopy "!folderName!\x86_64-w64-mingw32\bin\SDL2_ttf.dll" "%cd%\bins\" /e
rd /s /q "!folderName!"
del SDL2_ttf.tar.gz

xcopy "bins\*" . /s /i /y
rd /s /q bins



cls
echo INSTALLED!
echo(
pause
