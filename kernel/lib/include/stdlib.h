#ifndef STDLIB_H
#define STDLIB_H

#include <stdint.h>
#include <stddef.h>
#include "string.h"

#define NALLOC 1024 /* миним. число единиц памяти для запроса */
#define HEAP_SIZE 1024 * 1024  // 1 MB heap

union header { /* заголовок блока: */
    struct {
    union header *ptr; /* след. блок в списке свободных */
    unsigned size; /* размер этого блока */
    } s;
    long x; /* принудительное выравнивание блока */
};
typedef union header Header;

static Header base; /* пустой список для нач. запуска */
static Header *freep = NULL; /* начало в списке своб. блоков */
static uint8_t heap[HEAP_SIZE];
static void *program_break = heap; // Pointer to the current program break
static void *heap_end = heap + HEAP_SIZE; // Pointer to the end of the heap

void *sbrk(ptrdiff_t increment);
void *malloc(unsigned nbytes);
static Header *morecore(unsigned nu);
void *calloc(unsigned n, unsigned m);
void *realloc(void *bl, unsigned ns);
void free(void *ap);

#endif
