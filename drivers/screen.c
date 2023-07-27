#include "screen.h"
#include "../cpu/ports.h"
#include "../libc/mem.h"

int print_char(char character, int row, int col, char attribute_byte) {
    // Create a pointer to video memory
    unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;
    
    // Assume default color scheme if the attribute_byte is 0
    if (!attribute_byte)
        attribute_byte = WHITE_ON_BLACK;
    
    // Calculate memory location for the screen location
    int offset;
    // If screen co-ords are supplied, convert it to an offset
    if (row >= 0 && col >= 0)
        offset = get_screen_offset(row, col);
    // Otherwise, write at the cursor position
    else
        offset = get_cursor();

    // If the character is a newline, we should advance the cursor to the start of the next line
    if (character == '\n') {
        row = get_offset_row(offset);
        offset = get_screen_offset(row+1, 0);
    } 
    // Otherwise, write the character to screen
    else {
        vidmem[offset] = character;
        vidmem[offset+1] = attribute_byte;
        // Advance the cursor
        offset += 2;
    }

    offset = handle_scrolling(offset);
    set_cursor(offset);
    return offset;
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
    // Convert memory offset to a character offset
    offset /= 2; 
    // Tell the port we're writing the high byte
    port_byte_out(REG_SCREEN_CTRL, 14);
    // Write the high byte
    port_byte_out(REG_SCREEN_DATA, (unsigned char) (offset >> 8)); // make sure to do shift BEFORE casting
    // Tell the port we're writing the low byte
    port_byte_out(REG_SCREEN_CTRL, 15);
    // Now write the low byte
    port_byte_out(REG_SCREEN_DATA, (unsigned char) (offset & 0xff));
}

void print_at(char *message, int row, int col) {
    int offset;
    // If co-ords are supplied, set the cursor to those coords
    if (row >= 0 & col >= 0)
        set_cursor(get_screen_offset(row, col));

    int i=0;
    while (message[i] != 0) 
        print_char(message[i++], -1, -1, WHITE_ON_BLACK);
}
// Convenience method, user should use this as the public API
void print(char *message) {
    print_at(message, -1, -1);
}

void clear_screen()
{
    unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;
    for (int i=0; i<END_OF_SCREEN; i+=2) {
        vidmem[i] = 0x0;
        vidmem[i+1] = 0x0;
    }
    set_cursor(0);
}

int handle_scrolling(int cursor) {
    // If cursor goes beyond the end of screen memory
    if (cursor >= END_OF_SCREEN) {
        const unsigned char *vidmem = (unsigned char*) VIDEO_ADDRESS;
        // Copy line by line
        for (int row=0; row<MAX_ROWS; row++) {
            int currLine = vidmem + get_screen_offset(row, 0);
            int nextLine = vidmem + get_screen_offset(row+1, 0);
            mem_copy(nextLine, currLine, MAX_COLS*2);
        }
        /* int lastLine = get_screen_offset(MAX_ROWS-1, 0);
        for (int i=lastLine; i<END_OF_SCREEN; i++) {
            vidmem[lastLine] = 0;
        } */
        // Move cursor to last row, first col
        return get_screen_offset(MAX_ROWS-1, 0);
    } else {
        return cursor;
    }
}

int get_offset_row(int offset) {
    return offset / (MAX_COLS*2);
}
int get_offset_col(int offset) {
    return (offset - (get_offset_row(offset)*2*MAX_COLS))/2;
}