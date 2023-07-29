#include "keyboard.h"
#include "screen.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "../libc/string.h"

void delegate_keycode(u8int scancode);

static void keyboard_callback(registers_t r) {
    u8int scancode = port_byte_in(KEYBOARD_DATA_PORT);
    delegate_keycode(scancode);
}

void init_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_callback);
}

void delegate_keycode(u8int scancode) {
    switch (scancode) {
        case 2 ... 12: // Simple digit integer codes
            char ascii[2];
            int_to_ascii(scancode, ascii);
            print(ascii);
            break;
        case 16:
            print("q");
            break;
        case 17:
            print("w");
            break;
        case 18:
            print("e");
            break;
        case 19:
            print("r");
            break;
        case 20:
            print("t");
            break;
        case 21:
            print("y");
            break;
        case 22:
            print("u");
            break;
        case 23:
            print("i");
            break;
        case 24:
            print("o");
            break;
        case 25:
            print("p");
            break;
        case 26:
            print("[");
            break;
        case 27:
            print("]");
            break;
        case 28:
            print("\n");
            break;
        case 30:
            print("a");
            break;
        case 31:
            print("s");
            break;
        case 32:
            print("d");
            break;
        case 33:
            print("f");
            break;
        case 34:
            print("g");
            break;
        case 35:
            print("h");
            break;
        case 36:
            print("j");
            break;
        case 37:
            print("k");
            break;
        case 38:
            print("l");
            break;
        case 44:
            print("z");
            break;
        case 45:
            print("x");
            break;
        case 46:
            print("c");
            break;
        case 47:
            print("v");
            break;
        case 48:
            print("b");
            break;
        case 49:
            print("n");
            break;
        case 50:
            print("m");
            break;
        default:
            print("");
            break;
    }
}