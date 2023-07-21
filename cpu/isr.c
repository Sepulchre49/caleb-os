#include "../drivers/screen.h"
#include "isr.h"
#include "idt.h"

// List of exception messages
char *exception_messages[] = {
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

isr_t interrupt_handlers[256];
void register_interrupt_handler(u8int n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

void isr_handler(registers_t regs) {
    print("Received interrupt! ");
    print(exception_messages[regs.int_no]);
    print("\n");
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