; idt_load.asm
; takes a known `idt_pointer` label and passes it to `lidt` to load the IDT 
; stored at the label 

[BITS 32]
global idt_load
extern idt_pointer


idt_load:
    lidt [idt_pointer]
    ret
