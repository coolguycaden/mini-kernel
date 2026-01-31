#ifndef DRIVERS_KEYBOARD_H
#define DRIVERS_KEYBOARD_H 

#include "../../kernel/include/isrs.h"

// 8-bit READ-ONLY register that holds state
// of keyboard controller
#define KEYBOARD_STATUS_REG    0x64

#define KEYBOARD_DATA_READ      0x60 

// Writing to 0x60 sets flag that indicates a
// data write
#define KEYBOARD_DATA_WRITE     0x60 

// Writing to 0x64 sets flag that indicates a 
// command write 
#define KEYBOARD_COMMAND_WRITE  0x64 

// The first 32 (0x1F) interrupts vectors are defined
// and IBM standard show that keyboard will pull IRQ 1
// and we set the interrupt offset ot 0x20, thus our offset is
// 0x21
#define KEYBOARD_INTERRUPT_VECTOR 0x21
#endif 
