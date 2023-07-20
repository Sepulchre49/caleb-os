#include "../cpu/types.h"

#ifndef UTILS_H
#define UTILS_H
void mem_copy(u8int* source, u8int* dest, s32int size);
void mem_set(u8int* dest, u8int ch, u32int count);
#endif
