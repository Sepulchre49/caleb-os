#include "../drivers/screen.h"
#include "../cpu/idt.h"
#include "../cpu/timer.h"

void main() {
    clear_screen();
    print("Hello, world!\n");
    for (int i = 0; i < MAX_ROWS-2*1; i++) {
        print("Derp\n");
    }
    print("Okay!\n");

    init_idt();
    asm("sti");
    init_timer(50);

    asm("int $0x1");
    asm("int $0x2");
    asm("int $0x3");
    asm("int $0x4");
}