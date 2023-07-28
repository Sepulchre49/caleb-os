#ifndef IDT_H
#define IDT_H

#include "types.h"

// Kernel seg selector
#define KERNEL_CS 0x08

// Describes an interrupt gate
typedef struct {
    u16int base_lo;    // Lower 16 bits of interrupt routine address
    u16int sel;        // Kernel segment selector (0x08)
    u8int  always0;    // Must be zero
    u8int  flags;      // See documentation
    u16int base_hi;    // Upper 16 bits of interrupt routine address
} __attribute__((__packed__)) idt_entry_t;

// Special kind of pointer for the `lidt` instruction
// Describes a pointer to an array of interrupt handlers
typedef struct {
    u16int limit;
    u32int base;
} __attribute__((__packed__)) idt_ptr_t;

#define IDT_ENTRIES 256

void set_idt_gate(int n, u32int handler);
void set_idt();

#endif