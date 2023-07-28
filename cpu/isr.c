#include "../drivers/screen.h"
#include "ports.h"
#include "isr.h"
#include "idt.h"

isr_t interrupt_handlers[256];

void isr_install() {
    // CPU exception ISRs
    set_idt_gate(0,  (u32int)isr0);
    set_idt_gate(1,  (u32int)isr1);
    set_idt_gate(2,  (u32int)isr2);
    set_idt_gate(3,  (u32int)isr3);
    set_idt_gate(4,  (u32int)isr4);
    set_idt_gate(5,  (u32int)isr5);
    set_idt_gate(6,  (u32int)isr6);
    set_idt_gate(7,  (u32int)isr7);
    set_idt_gate(8,  (u32int)isr8);
    set_idt_gate(9,  (u32int)isr9);
    set_idt_gate(10, (u32int)isr10);
    set_idt_gate(11, (u32int)isr11);
    set_idt_gate(12, (u32int)isr12);
    set_idt_gate(13, (u32int)isr13);
    set_idt_gate(14, (u32int)isr14);
    set_idt_gate(15, (u32int)isr15);
    set_idt_gate(16, (u32int)isr16);
    set_idt_gate(17, (u32int)isr17);
    set_idt_gate(18, (u32int)isr18);
    set_idt_gate(19, (u32int)isr19);
    set_idt_gate(20, (u32int)isr20);
    set_idt_gate(21, (u32int)isr21);
    set_idt_gate(22, (u32int)isr22);
    set_idt_gate(23, (u32int)isr23);
    set_idt_gate(24, (u32int)isr24);
    set_idt_gate(25, (u32int)isr25);
    set_idt_gate(26, (u32int)isr26);
    set_idt_gate(27, (u32int)isr27);
    set_idt_gate(28, (u32int)isr28);
    set_idt_gate(29, (u32int)isr29);
    set_idt_gate(30, (u32int)isr30);
    set_idt_gate(31, (u32int)isr31);

    // Now remap the PIC to not conflict with CPU exceptions
    port_byte_out(PIC1_COMMAND, 0x11); // 0x11 is the "initialize" command
    port_byte_out(PIC2_COMMAND, 0x11);
    port_byte_out(PIC1_DATA, 0x20);    // New vector offset is 0x20, 0x28 respectively
    port_byte_out(PIC2_DATA, 0x28);
    port_byte_out(PIC1_DATA, 0x04);    // Send both PICS the cascade info
    port_byte_out(PIC2_DATA, 0x02);
    port_byte_out(PIC1_DATA, 0x01);    // Have both PICS use x86 mode
    port_byte_out(PIC2_DATA, 0x01);
    port_byte_out(PIC1_DATA, 0x0);     // Don't know what this does. Might be resetting Interrupt Mask Registers??
    port_byte_out(PIC2_DATA, 0x0);

    // Install IRQS
    set_idt_gate(32, (u32int)irq0);
    set_idt_gate(33, (u32int)irq1);
    set_idt_gate(34, (u32int)irq2);
    set_idt_gate(35, (u32int)irq3);
    set_idt_gate(36, (u32int)irq4);
    set_idt_gate(37, (u32int)irq5);
    set_idt_gate(38, (u32int)irq6);
    set_idt_gate(39, (u32int)irq7);
    set_idt_gate(40, (u32int)irq8);
    set_idt_gate(41, (u32int)irq9);
    set_idt_gate(42, (u32int)irq10);
    set_idt_gate(43, (u32int)irq11);
    set_idt_gate(44, (u32int)irq12);
    set_idt_gate(45, (u32int)irq13);
    set_idt_gate(46, (u32int)irq14);
    set_idt_gate(47, (u32int)irq15);

    set_idt();
}

// List of exception messages
static char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void isr_handler(registers_t regs) {
    print("Received interrupt! ");
    print(exception_messages[regs.int_no]);
    print("\n");
}

void register_interrupt_handler(u8int n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

void irq_handler(registers_t regs) {
    if (regs.int_no >= 40) {
        port_byte_out(PIC2_COMMAND, 0x20); // Send end of interrupt to PIC2
    }
    port_byte_out(PIC1_COMMAND, 0x20); // Send end of interrupt to PIC1

    if (interrupt_handlers[regs.int_no] != 0) {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
}