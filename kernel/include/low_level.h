#ifndef LOW_LEVEL_H
#define LOW_LEVEL_H

// C wrapper function that reads a byte from the specified port
unsigned char port_byte_read(unsigned short port);

// C wrapper function that writes a byte to specified port 
void port_byte_write(unsigned short port, unsigned char data);


// C wrapper function that reads word from specified port 
unsigned short port_word_read(unsigned short port);


// C wrapper function that writes word to specified port 
void port_word_write(unsigned short port, unsigned short data);

#endif
