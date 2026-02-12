#include "include/system.h"

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
    clear_screen();  
    print("Hello, Kernel!\n");
	print_hex(0xa2345678);			
	
    idt_setup();
    irq_setup();
    __asm__ __volatile__ ("sti");
    
    pit_setup_rate_generator(10); 
    timer_setup();
    keyboard_setup();

    while(1) {
    
    }

    return 0;
}


