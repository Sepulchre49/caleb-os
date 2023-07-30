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

void handle_command(char command[]) {
    char prefix[5] = {0};
    substring(command, prefix, 0, 4);
    if (compare(prefix, "echo") == true) {
        char arg[256] = {0};
        int len = strlen(command);
        substring(command, arg, 5, len);
        print(arg);
        print("\n");
    } 
    else if (compare(command, "tick") == true) {
        char timer_ascii[256] = {0};
        int currTick = tick();
        int_to_ascii(currTick, timer_ascii);
        print("The value of the timer tick is: ");
        print(timer_ascii);
        print("\n");
    }
    else {
        char stripped[256] = {0};
        print("`");
        print(command);
        print("` is not yet implemented.\n");
    }
}