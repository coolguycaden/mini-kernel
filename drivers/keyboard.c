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
    
    // F1 - F9 
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


// Certain scancodes (indexes to the above keyboard map)
// should not print anything when pressed (such as shift) 
const unsigned char Special_Scancodes [] = {
	29, // ctrl 
	42, // left shift 	
	54, // right shift 
	56, // alt 
	
	// F1 - F12 
	59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 87, 88,

	69, 70
};



// If a scancodes key is NOT 0, then it is printable  
unsigned char keyboard_is_printable(const unsigned scancode) {
	
	unsigned char character = Keyboard_US[scancode];
	
	// dirty hack for now
	if(character) {
		return 1; 
	}

	return 0; 
}

// Certain key presses should do something special (i.e., 'shift' press should
// capitalize letters or give alternate characters) 
void keyboard_handle_special_key_press(const unsigned char scancode) {
	
	
	switch(scancode) {
		
		// 42 / 54 are shifts, so set the status
		case 42:
		case 54:
			keyboard_status.shift_key = 1;
			break;

		default:
			break;

	};

}

// In the name 
void keyboard_handle_key_release(unsigned char scancode) {
	
	// KEYBOARD_KEY_RELEASED is set to 1 when key is released,
	// so unset bit so we can easily determine char value 
	scancode &= ~(KEYBOARD_KEY_RELEASED);

	switch(scancode) {

		// left and right shift key were released  
		case 42: case 54:
			keyboard_status.shift_key = 0;
			break; 

		// caps lock (pressing caps lock inverts its state) 
		case 58:
			keyboard_status.caps_lock = ~keyboard_status.caps_lock; 
			break; 

		// other special characters not considered now 
		default: 
			break; 
	}
}


void keyboard_handle_key_press(const unsigned char scancode) {
	unsigned char character = Keyboard_US[scancode];

	if(keyboard_is_printable(scancode)) {
		
		if(is_alpha(character)) {
			if(keyboard_status.caps_lock || keyboard_status.shift_key) {

				// Dirty ASCII hack: subtract 32 from a lower case letter
				// to get its upper case equivalent	
				character -= 32; 
			}
		}

		// Pass character, other args automatically get default
		// configurations 
		print_char(character, -1, -1, 0); 



	} else {
		
		keyboard_handle_special_key_press(scancode);
	}


}

void keyboard_isr(struct InterruptStackFrame * stack){

    // read scancode 
    unsigned char scancode = 0; 
    scancode = port_byte_read(KEYBOARD_DATA_READ);
	
	if(scancode & KEYBOARD_KEY_RELEASED) {

		keyboard_handle_key_release(scancode);	
	
	} else {

		keyboard_handle_key_press(scancode);	
	
	}
}




void keyboard_setup() {
    irq_register_handler(KEYBOARD_INTERRUPT_VECTOR, keyboard_isr);    
}
