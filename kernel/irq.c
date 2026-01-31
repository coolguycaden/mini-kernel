#include "include/system.h"
#include "include/isrs.h"

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

// list of irq handler functions 
static irq_t irq_handlers[16]; 

// Register an IRQ num with a handler, a function to service
// the IRQ 
void irq_register_handler(int irq_num, irq_t handler) {
    irq_handlers[irq_num] = handler; 
}

// Remove a handler from an IRQ 
void irq_remove_handler(int irq_num) {
    irq_handlers[irq_num] = 0;
}

// setup IRQs and load up their handlers into IDT 
void irq_setup() {
    pic_setup();

    idt_set_gate(32, (unsigned)irq0, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
    idt_set_gate(33, (unsigned)irq1, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
    idt_set_gate(34, (unsigned)irq2, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
    idt_set_gate(35, (unsigned)irq3, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
    idt_set_gate(36, (unsigned)irq4, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
    idt_set_gate(37, (unsigned)irq5, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
    idt_set_gate(38, (unsigned)irq6, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
    idt_set_gate(39, (unsigned)irq7, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
    idt_set_gate(40, (unsigned)irq8, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
    idt_set_gate(41, (unsigned)irq9, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
    idt_set_gate(42, (unsigned)irq10, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
    idt_set_gate(43, (unsigned)irq11, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
    idt_set_gate(44, (unsigned)irq12, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
    idt_set_gate(45, (unsigned)irq13, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
    idt_set_gate(46, (unsigned)irq14, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
    idt_set_gate(47, (unsigned)irq15, ISR_KERNEL_SELECTOR, ISR_ACCESS_FLAGS);
}


void irq_handler(struct InterruptStackFrame * stack) {
    
    irq_t handler = irq_handlers[stack->interrupt_num - 32];
    
    // If the handler for an IRQ exists, execute it 
    if(handler) {
        handler(stack);
    }

    
    // Send end-of-interrupt command to PIC 
    pic_send_eoi(stack->interrupt_num - 32);
}
