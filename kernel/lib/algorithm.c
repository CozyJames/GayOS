#include "include/algorithm.h"

void insert(char* buff, int index_point, int size, char sym) {
    for(int i = size; i > index_point; i--) {
        buff[i] = buff[i - 1];
    }
    buff[index_point] = sym;
}

void reverse(char* start, char* end) {
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}