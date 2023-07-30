#include "keyboard.h"
#include "screen.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "../libc/string.h"
#include "../libc/mem.h"

static char key_buffer[256];

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
            append('q', key_buffer);
            print("q");
            break;
        case 17:
            append('w', key_buffer);
            print("w");
            break;
        case 18:
            append('e', key_buffer);
            print("e");
            break;
        case 19:
            append('r', key_buffer);
            print("r");
            break;
        case 20:
            append('t', key_buffer);
            print("t");
            break;
        case 21:
            append('y', key_buffer);
            print("y");
            break;
        case 22:
            append('u', key_buffer);
            print("u");
            break;
        case 23:
            append('i', key_buffer);
            print("i");
            break;
        case 24:
            append('o', key_buffer);
            print("o");
            break;
        case 25:
            append('p', key_buffer);
            print("p");
            break;
        case 26:
            append('[', key_buffer);
            print("[");
            break;
        case 27:
            append(']', key_buffer);
            print("]");
            break;
        case 28:
            // Todo: send to shell
            print("\n");
            handle_command(key_buffer);
            mem_set(key_buffer, 0, 256);
            print("");
            break;
        case 30:
            append('a', key_buffer);
            print("a");
            break;
        case 31:
            append('s', key_buffer);
            print("s");
            break;
        case 32:
            append('d', key_buffer);
            print("d");
            break;
        case 33:
            append('f', key_buffer);
            print("f");
            break;
        case 34:
            append('g', key_buffer);
            print("g");
            break;
        case 35:
            append('h', key_buffer);
            print("h");
            break;
        case 36:
            append('j', key_buffer);
            print("j");
            break;
        case 37:
            append('k', key_buffer);
            print("k");
            break;
        case 38:
            append('l', key_buffer);
            print("l");
            break;
        case 44:
            append('z', key_buffer);
            print("z");
            break;
        case 45:
            append('x', key_buffer);
            print("x");
            break;
        case 46:
            append('c', key_buffer);
            print("c");
            break;
        case 47:
            append('v', key_buffer);
            print("v");
            break;
        case 48:
            append('b', key_buffer);
            print("b");
            break;
        case 49:
            append('n', key_buffer);
            print("n");
            break;
        case 50:
            append('m', key_buffer);
            print("m");
            break;
        case 57:
            append(' ', key_buffer);
            print(" ");
            break;
        default:
            print("");
            break;
    }
}