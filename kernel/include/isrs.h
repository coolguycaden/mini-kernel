#ifndef KERNEL_ISRS_H
#define KERNEL_ISRS_H

// Look at `FLAGS` defined in `idt.c`
// Explanation:
// present = 1, ring level = 0, -> 1000
// lower 5 bits must be '14'    -> 1110
#define ISR_ACCESS_FLAGS 0x8E

#define ISR_KERNEL_SELECTOR 0x08

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

// Define isr function pointer for callback
typedef void (*irq_t)(struct InterruptStackFrame*); 

extern void irq_register_handler(int irq_num, irq_t handler);

#endif 
