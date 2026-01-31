#ifndef KERNEL_SYSTEM_H
#define KERNEL_SYSTEM_H

// util.c externs 
extern void memory_copy(char * source, char * dest, int byte_amount);
extern void memory_set(char * dest, char value, int count);
extern void memory_set_word(short * dest, short value, int count);

// low_level.c externs 
extern unsigned char port_byte_read(unsigned short port);
extern void port_byte_write(unsigned short port, unsigned char data);
extern unsigned short port_word_read(unsigned short port);
extern void port_word_write(unsigned short port, unsigned short data);
extern inline void io_wait();

// idt.c externs
extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short selector, unsigned char flags);
extern void idt_setup();

// isrc.c externs 
//extern void isr_setup(); 

/***************************
 *
 * Driver Externs 
 *
 **************************/ 

// screen.c externs 
extern void print_char(char character, int col, int row, char attributes);
extern void print_at(char * string, int col, int row);
extern void print(char * string);
extern void print_hex(unsigned int value);
extern void clear_screen();



#endif
