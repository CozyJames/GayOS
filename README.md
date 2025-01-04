# GayOS

1. Установить инструменты GCC отсюда https://github.com/lordmilko/i686-elf-tools
2. В PATH указать на C:\i686-tools\bin 
3. Компилируем bootloader 
   ```
   i686-elf-as boot.s -o boot.o
   ```
4. Компилируем ядро
   ```
   i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
   ```
5. Линкуем ядро и bootloader в .bin через linker.ld
   ```
   i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc
   ```
6. Создаём образ
   ```
   mkdir -p isodir/boot/grub
   cp myos.bin isodir/boot/myos.bin
   cp grub.cfg isodir/boot/grub/grub.cfg
   grub-mkrescue -o myos.iso isodir
   ```

## To Do List
1. Поддержка ввода с клавиатуры
2. Скроллинг терминала
