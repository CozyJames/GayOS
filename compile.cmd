@echo off

echo [INFO] Compiling through Makefile...

wsl -d kali-linux make -s

echo [INFO] Copying files...

wsl -d kali-linux cp os.bin isodir/boot/os.bin
wsl -d kali-linux cp kernel/grub.cfg isodir/boot/grub/grub.cfg

:ask
set /p name=Enter a name for the .iso file [Default=GayOS]: 

if "%name%"=="" set name="GayOS"

wsl -d kali-linux grub-mkrescue -o %name%.iso isodir

echo [INFO] Creating ISO...

echo.
echo [INFO] Compiling done.

echo [INFO] Cleaning up...

wsl -d kali-linux rm -f *.o *.bin

:ask
set /p choice=Run the ISO on the virtual machine? (Y/N) [Default=Y]: 

if "%choice%"=="" set choice=Y

if /i "%choice%"=="Y" goto run
if /i "%choice%"=="N" goto end
echo Invalid choice. Please enter Y or N.
goto ask

:run
qemu-system-i386 -cdrom GayOS.iso
goto end

:end
pause


