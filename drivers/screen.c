#include "include/screen.h"
#include "../kernel/include/low_level.h"

// Get the offset required to print at a row-col combination on screen 
int get_screen_offset(int col, int row) {

    // To get to the target row, need to multiply the target by 
    // MAX_COLS (i.e., row width) 
    //
    // Then, we add the target colum to that result
    //
    // Now, we must multiply by 2 because EACH VIDEO CELL IS 2 BYTES! 
    int offset = ((row * MAX_COLS) + col) * 2;
    

    return offset; 
}

// Get the cursor's current position 
int get_cursor() {
    int offset = 0; 

    // The screen device uses its control register as an index
    // to select its internal registers, we care about:
    // 
    // REG 14: high byte of cursor's offset
    // REG 15: low byte of cursor's offset

    // Select REG 14 so we can read or write byte to it 
    port_byte_write(REG_SCREEN_CTRL, 14);
   
    // Read the high byte of cursor offset from REG 14 
    // shift left so the data is at the high byte 
    offset = port_byte_read(REG_SCREEN_DATA) << 8;

    // Select REG 15 
    port_byte_write(REG_SCREEN_CTRL, 15);

    // Get low byte cursor offset
    offset += port_byte_read(REG_SCREEN_DATA);

    // Remember, each video cell is 2 bytes,
    // and VGA hardware reports the characters, 
    // so we need to multiply it by 2 to get the
    // proper video cell offset 
    return offset * 2;     
}

void set_cursor(int offset) {
    
    // Convert from cell offset to char offset 
    offset /= 2; 

    // Like get_cursor, but instead we write our offset
    // to the registers 
    
    // Write high byte to REG 14 
    port_byte_write(REG_SCREEN_CTRL, 14);
    port_byte_write(REG_SCREEN_DATA, offset >> 8);

    // Write low byte to REG 15
    port_byte_write(REG_SCREEN_CTRL, 15);
    port_byte_write(REG_SCREEN_DATA, offset);
}


int handle_scrolling(int offset) {
    return offset; 
}

// Print a char on the screen at col, row, or at cursor position
void print_char(char character, int col, int row, char attributes) {
    
    unsigned char * video_memory = (unsigned char *) VIDEO_ADDRESS; 

    // If attributes aren't provided, we select default style 
    if(!attributes) {
        attributes = WHITE_ON_BLACK; 
    }

    // Get video memory ffset for the screen location 
    int offset;

    // If col and row are NOT negative, use them for offset 
    if(col >= 0 && row >= 0) {

        offset = get_screen_offset(col, row); 
    } else {
        
        offset = get_cursor(); 
    }
    
    // If we see a newline character, set offset to the end of
    // current row, so it will be advanced to the first col
    // of the next row .
    if(character == '\n') {

        int rows = offset / (2 * MAX_COLS); 
        offset = get_screen_offset(79, rows);
    } else {
        
        // Else, write character and attributes to video memory 
        // at calculated offset 
        video_memory[offset] = character; 
        video_memory[offset + 1] = attributes;
    }

    // Update offset to next character cell,
    // which is two bytes ahead of current cell 
    offset += 2; 

    // Make scrolling adjustment, when we reach bottom of screen
    offset = handle_scrolling(offset); 

    // Update cursor position on screen
    set_cursor(offset); 
}

// Print string to screen starting at col, row 
void print_at(char * string, int col, int row) {
    
    // Update cursor if col and row are NOT negative
    if(col >= 0 && row >= 0) {
        set_cursor(get_screen_offset(col, row));
    }

    // Loop through string and print each char 
    int x = 0;
    while(string[x] != 0) {
         
        print_char(string[x++], col, row, WHITE_ON_BLACK); 
    }
}

// Basic print function, just pass string 
void print(char * string) {
    print_at(string, -1, -1);
}
