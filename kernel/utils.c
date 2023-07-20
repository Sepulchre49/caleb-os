#include "utils.h"

void mem_copy(u8int *source, u8int *dest, s32int size) {
    const int MAX_COLS = 80;
    for (int i=0; i<2*MAX_COLS; i++)
        dest[i] = source[i];
}

void mem_set(u8int *dest, u8int ch, u32int count) {
    for (int i=0; i<count; i++) {
        dest[i] = ch;
    }
}