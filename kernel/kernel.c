#include "../drivers/include/screen.h"

// 0xb8000 begins video memory 
char * video_address = (char *) 0xb8000;

int cursor_offset = 0; 



// This function solely exists as a dump marker, 
// so I can know where functions are relative to this function
// when I am looking at the disassembly
void dump_marker() {
	int h1 = 0xabab;
	int h2 = 0xcdcd;
	int h3 = 0xdada; 
	int h4 = 0xfefe;
}

int main() {
    print_char('h', 0, 0, 0); 

    return 0;
}


