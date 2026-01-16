#include "include/util.h"

void memory_copy(char * source, char * dest, int byte_amount){
	
	for(int x = 0; x < byte_amount; x++) {
		dest[x] = source[x]; 
	}
}

void memory_set(char * dest, char value, int count) {
    
    for(int x = 0; x < count; x++) {
        dest[x] = value; 
    }
}

void memory_set_word(short * dest, short value, int count) {
    for(int x = 0; x < count; x++) {
        dest[x] = value; 
    }

}

int str_len(const char * str) {
    int length = 0;
    
    while(*str != 0) {
        length++;
        str++;
    }

    return length;
}
