@echo off

REM Assemble boot.s into an object file
i686-elf-as kernel\arch\i386\boot.s -o boot.o

REM Compile kernel.c
i686-elf-gcc -c kernel\kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

REM Link files
i686-elf-gcc -T kernel\arch\i386\linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

REM Copy files to isodir/boot using WSL in Kali
wsl -d kali-linux cp myos.bin isodir/boot/myos.bin

wsl -d kali-linux cp kernel/grub.cfg isodir/boot/grub/grub.cfg

REM Create ISO using WSL in Kali
wsl -d kali-linux grub-mkrescue -o myos.iso isodir

echo.
echo [INFO] Compiling done.

REM Ask the user if they want to run the ISO on the virtual machine
:ask
set /p choice=Do you want to run the ISO on the virtual machine? (Y/N) [Default=Y]: 

REM Default to N if no input is provided
if "%choice%"=="" set choice=Y

if /i "%choice%"=="Y" goto run
if /i "%choice%"=="N" goto end
echo Invalid choice. Please enter Y or N.
goto ask

:run
qemu-system-i386 -cdrom myos.iso
goto end

:end
pause
