#include "include/stdlib.h"

void *sbrk(ptrdiff_t increment) {
    void *old_break = program_break;
    void *new_break = (uint8_t *)program_break + increment;

    // Check for out-of-bounds conditions
    if (new_break < heap || new_break > heap_end) {
        return (void *)-1;  // Failure: Out of heap bounds
    }

    program_break = new_break;
    return old_break;  // Return the previous program break
}

/* morecore: запрашивает у системы дополнительную память */
static Header *morecore(unsigned nu) {
    if (nu < NALLOC) {
        nu = NALLOC;
    }
    char *cp = sbrk(nu * sizeof(Header));
    if (cp == (char *)-1) {
        return NULL;
    }
    Header *up = (Header *)cp;
    up->s.size = nu;
    free((void *)(up + 1));
    return freep;
}

void *malloc(unsigned nbytes) {
    Header *p, *prevp;
    Header *morecore(unsigned);
    unsigned nunits;
    nunits = (nbytes + sizeof (Header) - 1) / sizeof (Header) + 1;
    if ((prevp = freep) == NULL) { /* списка своб. памяти еще нет */
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) { /* достаточно большой */
            if (p->s.size == nunits) prevp->s.ptr = p->s.ptr;/* точно нужного размера */
            else { /* отрезаем хвостовую часть */
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);
        }
        if (p == freep) /* прошли полный цикл по списку */
        if ((p = morecore(nunits)) == NULL)
        return NULL; /* больше памяти нет */
    }
}

void *calloc(unsigned n, unsigned m) {
    if (n == 0 || m == 0) return NULL;
    unsigned total_size = n * m;
    void *ptr = malloc(total_size);
    if (ptr) {
        memset(ptr, 0, total_size);
    }
    return ptr;
}

void *realloc(void *bl, unsigned ns) {
    if (bl == NULL) {
        return malloc(ns);
    }
    if (ns == 0) {
        free(bl);
        return NULL;
    }
    Header *bp = (Header *)bl - 1;
    unsigned old_size = bp->s.size * sizeof(Header);
    if (ns <= old_size) {
        return bl;
    }
    void *new_block = malloc(ns);
    if (new_block == NULL) {
        return NULL;
    }
    memcpy(new_block, bl, old_size);
    free(bl);
    return new_block;
}

void free(void *ap) {
    Header *bp, *p;
    bp = (Header *)ap - 1; /* указатель на заголовок блока */
    for (p=freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) break; /* освобождаем блок в начале или в конце */
    if (bp + bp->s.size == p->s.ptr) { /* слить с верхним */
        bp->s.size += p->s.ptr->s.size; /* соседом */
        bp->s.ptr = p->s.ptr->s.ptr;
    } else 
        bp->s.ptr = p->s.ptr;
    if (p + p->s.size == bp) { /* слить с нижним соседом */
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else
        p->s.ptr = bp;
    freep = p;
}
