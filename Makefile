AS = i686-elf-as.exe
CC = i686-elf-gcc.exe

CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

all:
	$(AS) kernel/arch/i386/boot.s -o boot.o
	$(CC) -c kernel/kernel.c -o kernel.o $(CFLAGS)
	$(CC) -T kernel/arch/i386/linker.ld -o os.bin $(LDFLAGS)