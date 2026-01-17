extern void idt_load();
extern void memory_set(char * dest, int value, int count);

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
// DPL: 3 bits, Descriptior Privilege Level
// always: 5 bits = 01110 


struct IDTPtr {
    unsigned short limit;
    unsigned int base; 
} __attribute__((packed)); 

// There are 256 interrupt entries available,
// of which 0-31 are reserved 
struct IDTEntry32 idt[256]; 
struct IDTPtr idt_pointer; 

void idt_set_gate(unsigned char num, unsigned long base, unsigned short selector, unsigned char flags) {

    // Split provided base into low and high bytes 
    unsigned char base_high = (base >> 8) & 0xFF; 
    unsigned char base_low  = base & 0xFF; 

    idt[num].base_high_bits = base_high;
    idt[num].base_low_bits  = base_low;
    idt[num].selector = selector;
    idt[num].flags    = flags; 
    idt[num].zero     = 0;
}

void idt_install() {
    
    idt_pointer.limit = (sizeof (struct IDTEntry32) * 256) - 1;
    idt_pointer.base  = &idt_pointer;

    memory_set(&idt, 0, sizeof(struct IDTEntry32) * 256); 
}


