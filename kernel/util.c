// Simple memcopy clone, copies `byte_amount` from `source` to `dest`
void memory_copy(char * source, char * dest, int byte_amount){
	
	for(int x = 0; x < byte_amount; x++) {
		dest[x] = source[x]; 
	}
}

// Simple memset clone, sets `count` bytes at `dest` to `value` 
void memory_set(char * dest, char value, int count) {
    
    for(int x = 0; x < count; x++) {
        dest[x] = value; 
    }
}

// Simple memset clone, sets `count` word (16 bits) at `dest` to `value` 
void memory_set_word(short * dest, short value, int count) {
    for(int x = 0; x < count; x++) {
        dest[x] = value; 
    }

}

// Simple strlen clone, find length of string 
int str_len(const char * str) {
    int length = 0;
    
    while(*str != 0) {
        length++;
        str++;
    }

    return length;
}

// return 1 if alphabet, 0 if not  
unsigned char is_alpha(unsigned char character) {
	
	// simple ascii comparison:
	// a-z is 97 - 122
	// A-Z is 65 - 90 
	if(character < 65 || character > 122 ) {
		return 0; 
	} else if(character > 90 && character < 97) {
		return 0;
	}

	return 1; 
}

// return 1 if number, 0 if not 
unsigned char is_num(unsigned char character) {

	// simple ascii:
	// 0-9 is 48 - 57
	if(character < 48 || character > 57) {
		return 0;
	}

	return 1;
}
