#include "../drivers/include/screen.h"

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
    print("Hello, Kernel!");
    return 0;
}


