#include "include/system.h"

extern void idt_load(); 
extern void isr_setup(); 

// Interrupt Descriptor Entry, necessary to setup and handle interrupts
// this is the 32-bit version 
struct IDTEntry32 {
    unsigned short base_low_bits;  // base bits 0 - 15 
    unsigned short selector;       // kernel segment here  
    unsigned char  zero;           // ALWAYS 0 
    unsigned char  flags;          // see FLAGS comment below 
    unsigned short base_high_bits; // base bits 16 - 31
};
// FLAGS, bits 0 - 7, left to right 
// present: 1 bit, is segment present?
// DPL: 3 bits, Descriptor Privilege Level
// always: 5 bits = 01110 



// The struct necessary to pass to `lidt` to load the 
// described IDT 
struct IDTPtr {
    unsigned short limit;
    unsigned int base; 
} __attribute__((packed)); 



// There are 256 interrupt entries available,
// of which 0-31 are reserved 
struct IDTEntry32 idt[256]; 
struct IDTPtr idt_pointer; 

// Function that sets the interrupt at index `num` (0 indexed) to given address to execute when that
// interrupt is called 
void idt_set_gate(unsigned char num, unsigned long base, unsigned short selector, unsigned char flags) {

    unsigned short base_high = (base >> 16) & 0xFFFF;
    unsigned short base_low  = base & 0xFFFF; 
	
    idt[num].base_high_bits = base_high;
    idt[num].base_low_bits  = base_low;
    idt[num].selector = selector;
    idt[num].flags    = flags; 
    idt[num].zero     = 0;

}

// Basic setup of the IDT, including setting the ISRs for the 32 defined Intel faults
void idt_setup() {
    
	// Set to contain the entire `idt` array 
    idt_pointer.limit = (sizeof (struct IDTEntry32) * 256) - 1;
    idt_pointer.base  = &idt;

	// Ensure idt is empty (0) 
    memory_set(&idt, 0, sizeof(struct IDTEntry32) * 256); 
	
	// Basic implementation to setup each ISR for the 32 defined Intel faults 
	isr_setup();

	// Go to defined ASM function to utilize `lidt` to update the IDT 
	idt_load(); 
}
