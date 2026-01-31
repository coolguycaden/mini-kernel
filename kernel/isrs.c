#include "include/system.h"

// Look at `FLAGS` defined in `idt.c` 
// Explanation:
// present = 1, ring level = 0, -> 1000 
// lower 5 bits must be '14'    -> 1110
#define ISR_ACCESS_FLAGS 0x8E

#define KERNEL_SELECTOR 0x08

// Not sure how to do this a better way, so I will keep it like this for now
// Extern all the isrs that are defined in ASM in kernel/asm/interrupts.asm
// INTEL DEFINED INTERRUPTS 
extern void isr0(); 
extern void isr1(); 
extern void isr2(); 
extern void isr3(); 
extern void isr4(); 
extern void isr5(); 
extern void isr6(); 
extern void isr7(); 
extern void isr8(); 
extern void isr9(); 
extern void isr10(); 
extern void isr11(); 
extern void isr12(); 
extern void isr13(); 
extern void isr14(); 
extern void isr15(); 
extern void isr16(); 
extern void isr17(); 
extern void isr18(); 
extern void isr19(); 
extern void isr20(); 
extern void isr21(); 
extern void isr22(); 
extern void isr23(); 
extern void isr24(); 
extern void isr25(); 
extern void isr26(); 
extern void isr27(); 
extern void isr28(); 
extern void isr29(); 
extern void isr30(); 
extern void isr31(); 

// Software defined interrupts 
extern void isr32(); 
extern void isr33(); 
extern void isr34(); 
extern void isr35(); 
extern void isr36(); 
extern void isr37(); 
extern void isr38(); 
extern void isr39(); 
extern void isr40(); 


// Messages for the first 32 Intel defined faults 
const char * intel_exception_messages [] = {
	"Division By Zero", 
	"Debug", 
	"Non Maskable Interrupt", 
	"Breakpoint",
	"Overflow",
	"BOUND Range Exceeded",
	"Invalid Opcode", 
	"Device Not Available",
	"Double Fault",
	"Coprocessor Segment Overrun",
	"Invalid TSS",
	"Segment Not Present",
	"Stack-Segment Fault",
	"General Protection",
	"Page Fault",
	"Reserved",
	"x87 FPU Fploating-Point Error",
	"Alignment Check",
	"Machine Check",
	"SIMD Floating-Point Exception",
	"Virtualization Exception",
	"Control Protection Exception",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
}; 



// What the stackframe looks like after ISR was run 
struct InterruptStackFrame {
	// Segments pushed onto stack 
	unsigned int gs, fs, es, ds;

	// Pushed by `pusha` 
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eas;  

	// Pushed onto stack by `push byte` and error code 
	unsigned int interrupt_num, err_code; 

	// processor automatically pushes this 
	unsigned int eip, cs, eflags, user_esp, ss; 
};

// Not sure how to do this function better, 
// but simply sets the Intel defined faults (first 32 faults) to their respective implementations
void intel_isr_setup() {
	idt_set_gate(0, (unsigned) isr0, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(1, (unsigned) isr1, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(2, (unsigned) isr2, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(3, (unsigned) isr3, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(4, (unsigned) isr4, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(5, (unsigned) isr5, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(6, (unsigned) isr6, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(7, (unsigned) isr7, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(8, (unsigned) isr8, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(9, (unsigned) isr9, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);

	idt_set_gate(10, (unsigned) isr10, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(11, (unsigned) isr11, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(12, (unsigned) isr12, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(13, (unsigned) isr13, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(14, (unsigned) isr14, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(15, (unsigned) isr15, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(16, (unsigned) isr16, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(17, (unsigned) isr17, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(18, (unsigned) isr18, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(19, (unsigned) isr19, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(20, (unsigned) isr20, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);

	idt_set_gate(21, (unsigned) isr21, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(22, (unsigned) isr22, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(23, (unsigned) isr23, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(24, (unsigned) isr24, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(25, (unsigned) isr25, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(26, (unsigned) isr26, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(27, (unsigned) isr27, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(28, (unsigned) isr28, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(29, (unsigned) isr29, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(30, (unsigned) isr30, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(31, (unsigned) isr31, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);


}

// Same problem as above function, not sure how to make this more efficient
// This function sets any software up, starting at INT 32 (first interrupt after Intel's 32 defined interrupts) 
void software_isr_setup() {
	idt_set_gate(32, (unsigned) isr32, KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
}

// Sets up both Intel's defined ISRs and software-defined ISRs 
void isr_setup() {
	intel_isr_setup();
	software_isr_setup();
}

// Simple, when a fault is detected, print the message associated with that fault 
void fault_handler(struct InterruptStackFrame * stack) {
	
	// Intel defined fault handling  
	if (stack->interrupt_num < 32) {
		print("\n");
		print(intel_exception_messages[stack->interrupt_num]);
		print(" Exception. Halt!\n");
		while(1);
	} 
	else if (stack->interrupt_num <= 40) {
		// Handle software defined faults 
		
		
	}

		
}
