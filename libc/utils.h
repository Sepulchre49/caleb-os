#ifndef UTILS_H
#define UTILS_H

#include "../cpu/types.h"

void mem_copy(u8int* source, u8int* dest, s32int size);
void mem_set(u8int* dest, u8int ch, u32int count);

void int_to_ascii(int n, char str[]);
void reverse(char s[]);
int strlen(char s[]);
#endif
