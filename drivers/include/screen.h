#ifndef DRIVER_SCREEN_H
#define DRIVER_SCREEN_H

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS      25 
#define MAX_COLS      80 

// Default color scheme 
#define WHITE_ON_BLACK 0x0f 

// Screen device I/O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

// Manage screen offset 
int get_screen_offset(int col, int row);
int get_cursor();
int handle_scrolling(int offset);
void set_cursor(int offset);

// Printing functions 
void print_char(char character, int col, int row, char attributes);
void print_at(char * string, int col, int row);
void print(char * string);
void print_hex(unsigned char value); 

// Scrolling 
int handle_scrolling(int cursor_offset);
void clear_screen();

#endif
