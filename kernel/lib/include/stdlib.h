#ifndef STDLIB_H
#define STDLIB_H

#include <stdint.h>
#include <stddef.h>
#include "string.h"

#define NALLOC 1024 /* миним. число единиц памяти для запроса */
#define HEAP_SIZE (1024 * 1024)  // 1 MB heap

union header { /* заголовок блока: */
    struct {
    union header *ptr; /* след. блок в списке свободных */
    unsigned size; /* размер этого блока */
    } s;
    long x; /* принудительное выравнивание блока */
};
typedef union header Header;

void *sbrk(ptrdiff_t increment);
void *malloc(unsigned nbytes);
Header *morecore(unsigned nu);
void *calloc(unsigned n, unsigned m);
void *realloc(void *bl, unsigned ns);
void free(void *ap);

#endif
