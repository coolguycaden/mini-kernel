#include "include/low_level.h"

// C wrapper function that reads a byte from the specified port
unsigned char port_byte_read(unsigned short port) {
    unsigned char result;

    // "=a" result : means put AL register in variable RESULT
    // "d" (port)  : means load EDX with port 
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));

    return result;
}

// C wrapper function that writes a byte to specified port 
void port_byte_write(unsigned short port, unsigned char data) {
    // "a" (data) : means load EAX with data 
    // "d" (port) : means load EDX with port 
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port)); 
}


// C wrapper function that reads word from specified port 
unsigned short port_word_read(unsigned short port) {
    unsigned short result; 

    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port)); 

    return result;
}


// C wrapper function that writes word to specified port 
void port_word_write(unsigned short port, unsigned short data) {

    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));  
}
