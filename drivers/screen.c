#include "include/screen.h"
#include "../kernel/include/low_level.h"
#include "../kernel/include/util.h"

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

// set cursor at provided offset 
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


int handle_scrolling(int cursor_offset) {

	// If cursor is on the screen, no need to modify it
	if(cursor_offset < MAX_ROWS * MAX_COLS * 2) {
		return cursor_offset; 
	}

	// Move all rows up one
	for(int x = 0; x < MAX_ROWS; x++) {
		memory_copy(get_screen_offset(0, x) + VIDEO_ADDRESS,
					get_screen_offset(0, x - 1) + VIDEO_ADDRESS,
					MAX_COLS * 2
				);
	}

	char * last_line = get_screen_offset(0, MAX_ROWS - 1) + VIDEO_ADDRESS; 
	for(int x = 0; x < MAX_COLS * 2; x++) {
		last_line[x] = 0;

	}

	cursor_offset -= MAX_COLS * 2;

	return cursor_offset;
}



// In the name, clear the screen 
void clear_screen() {

	for(int row = 0; row < MAX_ROWS; row++) {
		
		for(int col = 0; col < MAX_COLS; col++) {
			print_char(' ', col, row, WHITE_ON_BLACK);
		}
	}

	set_cursor(get_screen_offset(0, 0));
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

// Print 32-bit number as hexadecimal 
void print_hex(unsigned int value) {

	for(int x = 7; x >= 0; x--) {
		
		// Simple loop: 
		// we shift the top 4 bits right until they are the 
		// bottom 4 bits 
		char hex_character = value >> (x * 4); 
	
		// Then, we AND the bottom 4 bits and 
		// 0x0F so we can select ONLY those 4 bits
		hex_character &= 0x0F; 

		// Now, we have a value from 0 - 15 (hex)
		// we can use an ASCII trick to get the character for
		// any hex value 
		//
		// Example: We take the value 0 and add the ASCII of 
		// '0' (48), we get 48 = '0', the char equivalent 
		// 
		// The same applies to 9 - 15 (a - f), but we add 55
		// so that 10 + 55 = 65, which is 'A' 
		if(hex_character <= 9) {
			hex_character += '0';
		} else {
			hex_character += 55;
		}

		print_char(hex_character, -1, -1, WHITE_ON_BLACK);
	}
}











