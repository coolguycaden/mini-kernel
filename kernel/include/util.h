#ifndef KERNEL_UTIL_H
#define KERNEL_UTIL_H

void memory_copy(char * source, char * dest, int byte_amount);
void memory_set(char * dest, char value, int count);
void memory_set_word(short * dest, short value, int count);

#endif 
