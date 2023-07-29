#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"

void main() {
    clear_screen();
    isr_install(); 
    asm("sti"); // Re-enable interrupts, not sure why it gets turned off
    init_timer(50);
    init_keyboard();
    print("Welcome to CalebOS!\n");
}