@echo off

echo PIXEL WARRIOR INSTALLER

echo downloading game executable
curl -o raw.githubusercontent.com/tymoshh/pixelWarrior/main/pixelWarrior.exe
echo

echo creating res folder and downloading resources
mkdir res
cd res
