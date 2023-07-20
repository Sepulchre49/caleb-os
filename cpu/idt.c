#include "idt.h"

extern void idt_flush(u32int address);
static void idt_set_gate(u8int idx, u32int isr_ptr, u16int selector, u8int flags);

// Interrupt vector
idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

void init_idt() {
    idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
    idt_ptr.base = (u32int) &idt_entries;

    // Clear garbage from interrupt routine vector
    mem_set(&idt_entries, 0, sizeof(idt_entry_t)*256);

    // Initialize the idt_entry for each slot in the vector
    idt_set_gate(0, (u32int)isr0, 0x08, 0x8e);
    idt_set_gate(1, (u32int)isr1, 0x08, 0x8e);
    idt_set_gate(2, (u32int)isr2, 0x08, 0x8e);
    idt_set_gate(3, (u32int)isr3, 0x08, 0x8e);
    idt_set_gate(4, (u32int)isr4, 0x08, 0x8e);
    idt_set_gate(5, (u32int)isr5, 0x08, 0x8e);
    idt_set_gate(6, (u32int)isr6, 0x08, 0x8e);
    idt_set_gate(7, (u32int)isr7, 0x08, 0x8e);
    idt_set_gate(8, (u32int)isr8, 0x08, 0x8e);
    idt_set_gate(9, (u32int)isr9, 0x08, 0x8e);
    idt_set_gate(10, (u32int)isr10, 0x08, 0x8e);
    idt_set_gate(11, (u32int)isr11, 0x08, 0x8e);
    idt_set_gate(12, (u32int)isr12, 0x08, 0x8e);
    idt_set_gate(13, (u32int)isr13, 0x08, 0x8e);
    idt_set_gate(14, (u32int)isr14, 0x08, 0x8e);
    idt_set_gate(15, (u32int)isr15, 0x08, 0x8e);
    idt_set_gate(16, (u32int)isr16, 0x08, 0x8e);
    idt_set_gate(17, (u32int)isr17, 0x08, 0x8e);
    idt_set_gate(18, (u32int)isr18, 0x08, 0x8e);
    idt_set_gate(19, (u32int)isr19, 0x08, 0x8e);
    idt_set_gate(20, (u32int)isr20, 0x08, 0x8e);
    idt_set_gate(21, (u32int)isr21, 0x08, 0x8e);
    idt_set_gate(22, (u32int)isr22, 0x08, 0x8e);
    idt_set_gate(23, (u32int)isr23, 0x08, 0x8e);
    idt_set_gate(24, (u32int)isr24, 0x08, 0x8e);
    idt_set_gate(25, (u32int)isr25, 0x08, 0x8e);
    idt_set_gate(26, (u32int)isr26, 0x08, 0x8e);
    idt_set_gate(27, (u32int)isr27, 0x08, 0x8e);
    idt_set_gate(28, (u32int)isr28, 0x08, 0x8e);
    idt_set_gate(29, (u32int)isr29, 0x08, 0x8e);
    idt_set_gate(30, (u32int)isr30, 0x08, 0x8e);
    idt_set_gate(31, (u32int)isr31, 0x08, 0x8e);
}

static void idt_set_gate(u8int idx, u32int isr_ptr, u16int selector, u8int flags) {
    idt_entry_t entry = {
       .base_lo = isr_ptr & 0xffff,
       .sel     = selector,
       .always0 = 0,
       .flags   = flags,
       .base_hi = isr_ptr >> 16 
    };
    idt_entries[idx] = entry;
}