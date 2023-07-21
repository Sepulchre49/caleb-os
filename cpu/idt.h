#include "types.h"

#ifndef IDT_H
#define IDT_H

#define PIC1            0x20      // Base address of controlling PIC
#define PIC2            0xa0      // Base address of secondary PIC
#define PIC1_COMMAND    PIC1
#define PIC1_DATA       (PIC1+1)
#define PIC2_COMMAND    PIC2
#define PIC2_DATA       (PIC2+1)

// Describes an interrupt gate
struct idt_entry {
    u16int base_lo;    // Lower 16 bits of interrupt routine address
    u16int sel;        // Kernel segment selector (0x08)
    u8int  always0;    // Must be zero
    u8int  flags;      // See documentation
    u16int base_hi;    // Upper 16 bits of interrupt routine address
} __attribute__((__packed__));
typedef struct idt_entry idt_entry_t;

// Special kind of pointer for the `lidt` instruction
// Describes a pointer to an array of interrupt handlers
struct idt_ptr {
    u16int limit;
    u32int base;
} __attribute__((__packed__));
typedef struct idt_ptr idt_ptr_t;

// Interrupt vector table initializer function
void init_idt();

// Assembly interrupt routines
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

#endif