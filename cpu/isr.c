#include "../drivers/screen.h"
#include "isr.h"

void isr_handler(registers_t regs) {
    print("Received interrupt!\n");
}