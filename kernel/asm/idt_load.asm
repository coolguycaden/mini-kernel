[BITS 32]
global idt_load
extern idt_pointer
_idt_load:
    lidt [idt_pointer]
    ret
