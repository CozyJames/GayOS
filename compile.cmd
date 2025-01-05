@echo off
REM Сборка boot.s в объектный файл
i686-elf-as kernel\arch\i386\boot.s -o boot.o

REM Компиляция kernel.c
i686-elf-gcc -c kernel\kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

REM Линковка
i686-elf-gcc -T kernel\arch\i386\linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

REM Копируем в isodir/boot (через WSL в Kali)
wsl -d kali-linux cp myos.bin isodir/boot/myos.bin

wsl -d kali-linux cp kernel/grub.cfg isodir/boot/grub/grub.cfg

REM Создаём ISO (через WSL в Kali)
wsl -d kali-linux grub-mkrescue -o myos.iso isodir

echo.
echo [INFO] Compiling done.
pause
