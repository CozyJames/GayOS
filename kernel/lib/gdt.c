#include "include/gdt.h"
#include "include/string.h"
#include "include/stdio.h"

#define GDT_ENTRIES 6

static struct gdt_entry gdt[GDT_ENTRIES];
static struct gdt_ptr gp;
static struct tss_entry tss;

/*
 * Вспомогательная функция для заполнения одной "строки" GDT.
 * idx: индекс в gdt[]
 * base, limit: границы сегмента
 * access: байт "access" (тип, DPL, Present)
 * gran: байт "granularity" (флаги, старшие 4 бита limit)
 */
static void gdt_set_gate(int idx, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    // Младшие 16 бит limit
    gdt[idx].limit_low    = (uint16_t)(limit & 0xFFFF);

    // Младшие 16 бит base
    gdt[idx].base_low     = (uint16_t)(base & 0xFFFF);
    // Следующие 8 бит base
    gdt[idx].base_middle  = (uint8_t)((base >> 16) & 0xFF);
    // Старшие 8 бит base
    gdt[idx].base_high    = (uint8_t)((base >> 24) & 0xFF);

    // Access byte
    gdt[idx].access       = access;

    // Granularity (старшие 4 бита limit + флаги)
    // Например, если granularity=0xCF, тогда:
    // - старшие 4 бита limit (0xF) => limit >>= 12 и G = 1 => 4К страницы
    gdt[idx].granularity  = (uint8_t)((limit >> 16) & 0x0F);
    gdt[idx].granularity |= gran & 0xF0; 
}

static void write_tss(uint32_t idx, uint16_t ss0, uint32_t esp0)
{
    uint32_t base = (uint32_t)&tss;
    uint32_t limit = sizeof(tss) - 1;

    gdt_set_gate(idx, base, limit, 0xE9, 0x00);

    memset(&tss, 0, sizeof(tss));

    tss.ss0 = ss0;
    tss.esp0 = esp0;
    tss.cs = 0x08; 
    tss.ss = tss.ds = tss.es = tss.fs = tss.gs = 0x10;
}

bool gdt_verify(void)
{
    /*
     * Считаем текущий GDTR в локальную структуру check.
     * Затем сравним base/limit с тем, что мы установили (gp).
     */
    struct gdt_ptr check;
    __asm__ volatile ("sgdt %0" : "=m"(check));
    return (check.base == gp.base && check.limit == gp.limit);
}

void gdt_install(void)
{
    // Указываем размер = (число записей * 8) - 1
    gp.limit = (sizeof(struct gdt_entry) * GDT_ENTRIES) - 1;
    // База = адрес массива gdt
    gp.base = (uint32_t)&gdt;

    // 1) NULL дескриптор (все нули)
    gdt_set_gate(0, 0, 0, 0, 0);

    // 2) Код-сегмент ядра (ring 0):
    // base=0, limit=0xFFFFFFFF => покрывает всю память (4Гб).
    // access=0x9A => Present=1, Ring=0, Executable=1, Code segment=1, Readable=1
    // gran=0xCF => Page-granularity=1 (4К), 32-бит, LimitHigh=0xF
    gdt_set_gate(1, 
                 0, 
                 0xFFFFFFFF, 
                 0x9A,   // 10011010b
                 0xCF);  // 11001111b

    // 3) Дата-сегмент ядра (ring 0):
    // access=0x92 => Present=1, Ring=0, Executable=0, Data segment=1, Writable=1
    // gran=0xCF => то же, что выше
    gdt_set_gate(2, 
                 0, 
                 0xFFFFFFFF, 
                 0x92,   // 10010010b
                 0xCF);  // 11001111b
                 
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // user code
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // user data

    write_tss(5, 0x10, 0x0);

    gdt_flush((uint32_t)&gp);
    tss_flush(0x28);
}