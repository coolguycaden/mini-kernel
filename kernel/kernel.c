#define WHITE_ON_BLACK 0x0F 

// 0xb8000 begins video memory 
char * video_address = (char *) 0xb8000;

// Prints string to screen, does NOT auto scroll
// prints to same location on the screen
void print_string(char * string) {
	
	char * video_memory = video_address;
	
	// Continue until we find null-termiantor 
	while(*string != 0) {

		// Each video cell is a sequence of two bytes:
		// [Character] and [Attribute]
		// So first, load the char into the cell 
		*video_memory = *string;

		// Now, load in the attribute for the char 
		// with "WHITE_ON_BLACK" attribute 
		*(video_memory + 1) = WHITE_ON_BLACK;

		// go to next char 
		string++;

		// go to next CELL in video memory 
		video_memory += 2; 
		
	}	
}

void test() {
	int h1 = 0xabab;
	int h2 = 0xcdcd;
	int h3 = 0xdada; 
	int h4 = 0xfefe;
}

int main() {
	char * string = "Hello, World!";
	print_string(string);
	
	char * video_memory = (char *) 0xb8000;
	*video_memory = 'X';

	return 0;
}


