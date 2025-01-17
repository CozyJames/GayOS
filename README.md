# GayOS

## Требования для Windows
- Компилятор GCC [i686-elf-tools](https://github.com/lordmilko/i686-elf-tools). _**В PATH указать на i686-tools\bin**_ 
- QEMU (system-i386). _**В PATH указать на папку \qemu**_ 
- WSL (kali-linux) `wsl --install -d kali-linux`. _**Установка через PowerShell**_
- создать папки isodir/boot/grub там же где и compile.cmd
### Требования внутри WSL
- `sudo apt install grub-legacy`
- `sudo apt install grub-pc-bin`
- `sudo apt install xorriso`
- `sudo apt install make`

## Запуск через compile.cmd
1. В Makefile указать собственный путь на компилятор `ELFDIR  = .../i686-tools/lib/gcc/i686-elf/13.2.0`
2. _(Опционально)_ Изменить значения `CFLAGS` и `LDFLAGS` на необходимые

## Ручной запуск
1. В Makefile указать собственный путь на компилятор `ELFDIR  = .../i686-tools/lib/gcc/i686-elf/13.2.0`
2. _(Опционально)_ Изменить значения `CFLAGS` и `LDFLAGS` на необходимые
3. Запускаем WSL
4. Запускаем Makefile командой `make -s`
5. Копируем конфиг и бинарник в isodir
- `cp os.bin isodir/boot/os.bin`
- `cp kernel/grub.cfg isodir/boot/grub/grub.cfg`
7. Создаём ISO `grub-mkrescue -o GayOS.iso isodir`
8. Запускаем ISO через qemu `qemu-system-i386 -cdrom GayOS.iso`

## To Do List
1. Поддержка ввода с клавиатуры
2. Скроллинг терминала
3. ~~Защита стека~~
5. Глобальная таблица дескрипторов
6. Memory management
7. Отладить вывод вещественного числа после запятой (Важно!!!!!)
