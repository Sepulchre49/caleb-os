#include "keyboard.h"
#include "screen.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "../libc/string.h"

static void keyboard_callback(registers_t r) {
    u8int scancode = port_byte_in(KEYBOARD_DATA_PORT);
    char string[256];    
    int_to_ascii(scancode, string);
    print("Keyboard interrupt detected! ");
    print(string);
    print("\n");
}

void init_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_callback);
}

void 