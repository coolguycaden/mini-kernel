#include "include/util.h"

void memory_copy(char * source, char * dest, int byte_amount){
	
	for(int x = 0; x < byte_amount; x++) {
		dest[x] = source[x]; 
	}
}
