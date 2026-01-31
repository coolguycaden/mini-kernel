#include "include/system.h"
#include "include/isrs.h"

// Messages for the first 32 Intel defined isrs 
const char * isr_messages [] = {
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


// INTEL DEFINED ISRS
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





// Not sure how to do this function better, 
// but simply sets the Intel defined isrs (first 32 isrs) to their respective implementations
void isr_setup() {
	idt_set_gate(0, (unsigned) isr0, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(1, (unsigned) isr1, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(2, (unsigned) isr2, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(3, (unsigned) isr3, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(4, (unsigned) isr4, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(5, (unsigned) isr5, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(6, (unsigned) isr6, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(7, (unsigned) isr7, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(8, (unsigned) isr8, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(9, (unsigned) isr9, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);

	idt_set_gate(10, (unsigned) isr10, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(11, (unsigned) isr11, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(12, (unsigned) isr12, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(13, (unsigned) isr13, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(14, (unsigned) isr14, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(15, (unsigned) isr15, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(16, (unsigned) isr16, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(17, (unsigned) isr17, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(18, (unsigned) isr18, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(19, (unsigned) isr19, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(20, (unsigned) isr20, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);

	idt_set_gate(21, (unsigned) isr21, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(22, (unsigned) isr22, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(23, (unsigned) isr23, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(24, (unsigned) isr24, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(25, (unsigned) isr25, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(26, (unsigned) isr26, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(27, (unsigned) isr27, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(28, (unsigned) isr28, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(29, (unsigned) isr29, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(30, (unsigned) isr30, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
	idt_set_gate(31, (unsigned) isr31, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
}

// Simple, when a isr is detected, print the message associated with that fault 
void isr_handler(struct InterruptStackFrame * stack) {

	// Intel defined isr handling  
	if (stack->interrupt_num < 32) {
		print("\n");
		print(isr_messages[stack->interrupt_num]);
		print(" Exception.\n");
		while(1);
	} 
   		
}
