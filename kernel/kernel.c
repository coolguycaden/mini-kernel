extern void print(char * string); 
extern void print_hex(unsigned int value); 

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
	print_hex(0xa2345678);	
    

    return 0;
}


