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

void print_char(char character, int col, int row, char attributes);

#endif
