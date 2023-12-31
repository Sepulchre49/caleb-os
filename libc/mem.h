#ifndef MEM_H
#define MEM_H

#include "../cpu/types.h"

void mem_copy(u8int *source, u8int *dest, s32int size);
void mem_set(u8int *dest, u8int ch, u32int count);

#endif