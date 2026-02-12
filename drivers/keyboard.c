#include "../kernel/include/system.h"
#include "include/keyboard.h"
#include "../kernel/include/isrs.h"


struct KeyboardStatus {
    unsigned char alt_key : 1;
    unsigned char control_key : 1; 
    unsigned char shift_key : 1;
    unsigned char caps_lock : 1; 
    unsigned char num_lock : 1;
    unsigned char scroll_lock : 1; 
    unsigned char unused : 2; 
} __attribute__((packed));

struct KeyboardStatus keyboard_status = {
    .alt_key = 0,
    .control_key = 0,
    .shift_key = 0,
    .caps_lock = 0,
    .num_lock = 0, 
    .scroll_lock = 0,
    .unused = 0,
};

const unsigned char Keyboard_US[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	
    '9', '0', '-', '=', 
    '\b', // backspace 
    '\t',  // tab 
    'q', 'w', 'e', 'r',	
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', 
    '\n', // enter 
    0,	   // ctrl 
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
    '\'', '`',   
    0,	// left shift 
    '\\', 'z', 'x', 'c', 'v', 'b', 'n',	
    'm', ',', '.', '/',   
    0, // right shift 		
    '*',
    0,	// alt 
    ' ', // space bar 
    0,	// caps lock 
    
    // F1 - 59 
    0,	0,   0,   0,   0,   0,   0,   0,   0,
    0,	// F10 
    0,	// num lock 
    0,	// scroll lock 
    0,	// home 
    0,	// up arrow 
    0,	// page up 
    '-',
    0,	// left arrow 
    0,
    0,	// right arrow 
    '+',
    0,	// end 
    0,	// down arrow 
    0,	// page down 
    0,	// insert 
    0,	// delete 
    0,   0,   0,
    0,	// F11 
    0,	// F12 
    0,	// All other keys are undefined

};


unsigned char keyboard_is_special_char(unsigned char character) {
	
	return 0;
}

// steps for logic:
// read scancode
// if special character (! caps 

void keyboard_isr(struct InterruptStackFrame * stack){

    // read scancode 
    unsigned char scancode = 0; 
    scancode = port_byte_read(KEYBOARD_DATA_READ);

	if(scancode & KEYBOARD_KEY_RELEASED) {

		// remove bit manually so we can easily determine char value 
		scancode &= ~(KEYBOARD_KEY_RELEASED);

		// TODO: handle release of special keys 
		switch(scancode) {
			
			// left and right shift key 
			case 42: case 54:
				keyboard_status.shift_key = ~keyboard_status.shift_key;
				break; 

			// caps lock 
			case 48:
				keyboard_status.caps_lock = ~keyboard_status.caps_lock; 
				break; 
			
			default: 
				break; 
		}
	} else {
		unsigned char character = Keyboard_US[scancode];

		// if caps lock or shift key, capitalize letter 
		if(keyboard_status.caps_lock | keyboard_status.shift_key) {
			// Dirty ASCII hack: subtract 32 from a lower case letter
			// to get its upper case equivalent
			character -= 32;
		}


		// key was released AND printable, print it 
		print_char(character, -1, -1, 0);
	}
}




void keyboard_setup() {
    irq_register_handler(KEYBOARD_INTERRUPT_VECTOR, keyboard_isr);    
}
