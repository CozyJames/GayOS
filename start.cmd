@echo off

:ask
set /p name=Enter the name of your .iso file [Default=GayOS]
if "%name%"=="" set name="GayOS"

echo [INFO] Starting QEMU...

qemu-system-i386 -cdrom %name%.iso