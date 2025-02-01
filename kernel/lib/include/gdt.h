#ifndef GDT_H
#define GDT_H

#include <stdbool.h>
#include <stdint.h>


/*
 * Структура одного дескриптора GDT (8 байт)
 * Поля __attribute__((packed)) нужны, чтобы компилятор не добавлял выравнивание.
 */
struct gdt_entry {
    uint16_t limit_low;      // Нижние 16 бит "Limit"
    uint16_t base_low;       // Нижние 16 бит "Base"
    uint8_t  base_middle;    // Следующие 8 бит "Base"
    uint8_t  access;         // Байт "Access" (присутствие, DPL, тип сегмента и т.д.)
    uint8_t  granularity;    // Байт "Granularity" (старшие 4 бита Limit, флаги)
    uint8_t  base_high;      // Старшие 8 бит "Base"
} __attribute__((packed));

/*
 * Указатель на GDT: тут хранится размер (limit) и адрес (base) массива gdt.
 * Используется командой LGDT.
 */
struct gdt_ptr {
    uint16_t limit;   // Размер GDT - 1
    uint32_t base;    // Адрес начала GDT
} __attribute__((packed));

struct tss_entry {
    uint32_t prev_tss;   // Сегмент предыдущей TSS
    uint32_t esp0;       // Стек ядра
    uint32_t ss0;        // Сегмент стека ядра
    uint32_t esp1;       // Стек привилегий 1
    uint32_t ss1;        // Сегмент стека привилегий 1
    uint32_t esp2;       // Стек привилегий 2
    uint32_t ss2;        // Сегмент стека привилегий 2
    uint32_t cr3;        // Регистр CR3
    uint32_t eip;        // Регистр EIP
    uint32_t eflags;     // Регистр EFLAGS
    uint32_t eax;        // Регистр EAX
    uint32_t ecx;        // Регистр ECX
    uint32_t edx;        // Регистр EDX
    uint32_t ebx;        // Регистр EBX
    uint32_t esp;        // Регистр ESP
    uint32_t ebp;        // Регистр EBP
    uint32_t esi;        // Регистр ESI
    uint32_t edi;        // Регистр EDI
    uint32_t es;         // Сегмент ES
    uint32_t cs;         // Сегмент CS
    uint32_t ss;         // Сегмент SS
    uint32_t ds;         // Сегмент DS
    uint32_t fs;         // Сегмент FS
    uint32_t gs;         // Сегмент GS
    uint32_t ldt;        // Сегмент LDT
    uint16_t trap;       // Флаг отладки
    uint16_t iomap_base; // Базовый адрес I/O Map
} __attribute__((packed));


void gdt_install(void);
bool gdt_verify(void);

uint16_t get_tr(void);
void gdt_debug(void);

extern void gdt_flush(uint32_t);
extern void tss_flush(uint16_t);


#endif /* GDT_H */