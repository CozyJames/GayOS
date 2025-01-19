#ifndef STRING_H
#define STRING_H

#include <stddef.h>

size_t strlen(const char* str);
int strcmp(const char* string1, const char* string2);
void *memset(void *memptr, int val, unsigned num);

#endif /* STRING_H */
