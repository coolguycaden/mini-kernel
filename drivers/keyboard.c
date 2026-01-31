#include "../kernel/include/system.h"
#include "include/keyboard.h"
#include "../kernel/include/isrs.h"

void keyboard_isr(struct InterruptStackFrame * stack){
    char str[2]; 
    str[0] = port_byte_read(KEYBOARD_DATA_READ);
    str[1] = '\0'; 
    print(str);
}

void keyboard_setup() {
    irq_register_handler(KEYBOARD_INTERRUPT_VECTOR, keyboard_isr);    
}
