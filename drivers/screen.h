#ifndef SCREEN_H
#define SCREEN_H

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
// Attribute byte for our default color scheme
#define WHITE_ON_BLACK 0x0f
#define END_OF_SCREEN 2*(MAX_ROWS*MAX_COLS)

// Screen device I/O ports (for the cursor)
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

int print_char(char character, int row, int col, char attribute_byte);
int get_screen_offset(int row, int col);

int get_cursor();
void set_cursor(int offset); 

void print_at(char *message, int row, int col);
void print(char *message);

void clear_screen();
int handle_scrolling(int cursor);

int get_offset_row(int offset);
int get_offset_col(int offset);

#endif