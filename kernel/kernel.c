#include "../drivers/screen.h"

void main() {
    clear_screen();
    print("Hello, world!\n");
    for (int i = 0; i < MAX_ROWS-2*1; i++) {
        print("Derp\n");
    }
    print("Okay!\n");
}