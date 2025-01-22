#include "include/string.h"

size_t strlen(const char *str)
{
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

int strcmp(const char *string1, const char *string2) {
    size_t len_string1 = strlen(string1);
    size_t len_string2 = strlen(string2);
    if(len_string1 != len_string2) return 1;
    for(size_t i = 0; i < len_string1; i++) {
        if(string1[i] != string2[i]) return 1;
    }
    return 0;
}

void *memset(void *memptr, int val, unsigned num) {
    unsigned char *m = (unsigned char *)memptr;
    for (size_t i = 0; i < num; i++) {
        m[i] = (unsigned char)val;
    }
    return memptr;
}

void *memcpy(void *dest, void *src, size_t count) {
    unsigned char *d = (unsigned char*)dest;
    unsigned char *s = (unsigned char*)src;
    for (size_t i = 0; i < count; i++) d[i] = s[i];
    return dest;
}