#include "idt.h"
#include "ports.h"
#include "../libc/mem.h"

idt_entry_t idt[IDT_ENTRIES];
idt_ptr_t idt_ptr;

void set_idt_gate(int n, u32int handler) {
    idt[n].base_lo = handler & 0xffff;
    idt[n].sel     = KERNEL_CS;
    idt[n].always0 = 0;
    idt[n].flags   = 0x8e;
    idt[n].base_hi = (handler >> 16) & 0xffff;
}

void set_idt() {
    idt_ptr.base = (u32int) &idt;
    idt_ptr.limit = IDT_ENTRIES * sizeof(idt_entry_t) - 1;
    asm volatile ("lidtl (%0)" : : "r" (&idt_ptr));
}