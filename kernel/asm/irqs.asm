; Define a macro that takes one argument (%1)
%macro IRQ_NOERRCODE 1
  global irq%1
  irq%1:
      cli

      ; Push dummy error code 
      push byte 0
	  
      ; Add 31 because first 32 interrupts
      ; (0x1F) are defined, so we must start
      ; at 0x20 = 32 
      push byte (%1 + 32)


      jmp irq_common_stub
%endmacro

IRQ_NOERRCODE 0
IRQ_NOERRCODE 1
IRQ_NOERRCODE 2
IRQ_NOERRCODE 3
IRQ_NOERRCODE 4
IRQ_NOERRCODE 5
IRQ_NOERRCODE 6
IRQ_NOERRCODE 7
IRQ_NOERRCODE 8
IRQ_NOERRCODE 9
IRQ_NOERRCODE 10
IRQ_NOERRCODE 11
IRQ_NOERRCODE 12
IRQ_NOERRCODE 13
IRQ_NOERRCODE 14
IRQ_NOERRCODE 15

extern irq_handler 

irq_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov eax, esp
    push eax

    mov eax, irq_handler
    call eax
    
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    
    add esp, 8
    
    iret
