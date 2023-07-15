#include "screen.h"
#include "../kernel/low_level.h"

void print_char(char character, int row, int col, char attribute_byte) {
    // Create a pointer to video memory
    unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;
    
    // Assume default color scheme if the attribute_byte is 0
    if (!attribute_byte)
        attribute_byte = WHITE_ON_BLACK;
    
    // Calculate memory location for the screen location
    int offset;
    // If screen co-ords are non-negative, convert it to an offset
    if (row >= 0 && col >= 0)
        offset = get_screen_offset(row, col);
    // Otherwise, write at the cursor position
    else
        offset = get_cursor();

    // If the character is a newline, we should advance the cursor to the end of the current line
    if (character == '\n') {
        int row = get_offset_row(offset);
        offset = get_screen_offset(row, 79);
    } 
    // Otherwise, write the character to screen
    else {
        vidmem[offset] = character;
        vidmem[offset+1] = attribute_byte;
    }

    // Advance the cursor
    offset += 2;
    //offset = handle_scrolling(offset);
    set_cursor(offset);
}

int get_screen_offset(int row, int col) {
    return 2*(row * MAX_COLS + col);
}

int get_cursor() {
    // Set ctrl register to high byte (14)
    port_byte_out(REG_SCREEN_CTRL, 14);
    // Get the high byte
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;
    // Set ctrl register to low byte (15)
    port_byte_out(REG_SCREEN_CTRL, 15);
    // Get the low byte
    offset += port_byte_in(REG_SCREEN_DATA);
    // Cursor offset reported by VGA hardware is # of characters,
    // need to multiply by 2 to count the attribute byte
    return offset*2;
}

void set_cursor(int offset) {
    // Set memory offset to a character offset)
    offset /= 2; 
    // Tell the port we're writing to the high byte
    port_byte_out(REG_SCREEN_CTRL, 14);
    // Write the high byte
    port_byte_out(REG_SCREEN_DATA, (unsigned char) offset >> 8);
    // Tell the port we're writing the low byte
    port_byte_out(REG_SCREEN_CTRL, 15);
    // Now set the low byte
    port_byte_out(REG_SCREEN_DATA, (unsigned char) offset);
}

void print_at(char *message, int row, int col) {
    int offset;
    if (row >= 0 & col >= 0)
        set_cursor(get_screen_offset(row, col));

    int i=0;
    while (message[i] != 0) {
        print_char(message[i++], row, col, WHITE_ON_BLACK);
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}
void print(char *message) {
    print_at(message, -1, -1);
}

int get_offset_row(int offset) {
    return offset / (MAX_COLS*2);
}
int get_offset_col(int offset) {
    return (offset - (get_offset_row(offset)*2*MAX_COLS))/2;
}