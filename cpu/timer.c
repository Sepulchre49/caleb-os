#include "timer.h"
#include "isr.h"
#include "ports.h"
#include "../drivers/screen.h"   
#include "../libc/string.h"

u32int tick = 0;

static void timer_callback(registers_t regs) {
    tick++;
    print("");
    /* tick++; */
    /* print("Tick: "); */
    /* char tick_ascii[256]; */
    /* int_to_ascii(tick, tick_ascii); */
    /* print(tick_ascii); */
    /* print("\n"); */
}

void init_timer(u32int freq) {
    register_interrupt_handler(IRQ0, timer_callback);

    u32int divisor = 1193180 / freq;

    // Send command byte
    port_byte_out(0x43, 0x36);

    u8int low = (u8int) (divisor & 0xff);
    u8int hi  = (u8int) ((divisor >> 8) & 0xff);
    
    port_byte_out(0x40, low);
    port_byte_out(0x40, hi);
}