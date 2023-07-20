#include "types.h"
#ifndef ISR_H
#define ISR_H

typedef struct {
    u32int ds;
    u32int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    u32int int_no, err_code;
    u32int eip, cs, eflags, useresp, ss;
} registers_t;
#endif