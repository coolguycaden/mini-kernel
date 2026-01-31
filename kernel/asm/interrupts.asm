; interrupts.asm 
; Uses macros to define the first 32 defined Intel faults
; Sets so that each fault jumps to `isr_common_stub` which will setup
; stack so a C function `fault_handler` can parse the fault


; Define a macro that takes one argument (%1)
%macro ISR_NOERRCODE 1
  global isr%1
  isr%1:
      cli

      ; Push dummy error code 
      push byte 0
	  push byte %1


      jmp isr_common_stub
%endmacro

; Define a macro for ISRs that already push an error code
%macro ISR_ERRCODE 1
  global isr%1
  isr%1:
      cli
      
      ; No dummy error code push needed
      push byte %1

      jmp isr_common_stub
%endmacro

; ISR WITH NO ErrCodes 
ISR_NOERRCODE 0     ; Divide Error 
ISR_NOERRCODE 1     ; Debug Exception
ISR_NOERRCODE 2     ; NMI interrupt 
ISR_NOERRCODE 3     ; Breakpoint
ISR_NOERRCODE 4     ; Overflow 
ISR_NOERRCODE 5     ; BOUND range exceeded 
ISR_NOERRCODE 6     ; Invalid opcode 
ISR_NOERRCODE 7     ; Device not available 
ISR_NOERRCODE 9     ; Coprocessor segment overrun 
ISR_NOERRCODE 16    ; x87 FPU Floating Point Error 
ISR_NOERRCODE 18    ; Machine Check 
ISR_NOERRCODE 19    ; SIMD Floating Point Exception 
ISR_NOERRCODE 20    ; Virtualization Exception 

; ISRs WITH ErrCodes 
ISR_ERRCODE 8 		; Double Fault 
ISR_ERRCODE 10 		; Invalid TSS 
ISR_ERRCODE 11 		; Segment Not Present 
ISR_ERRCODE 12  	; Stack-Segment Fault 
ISR_ERRCODE 13 		; General Protection 
ISR_ERRCODE 14 		; Page Fault 
ISR_ERRCODE 17 		; Alignment check 
ISR_ERRCODE 21 		; Control Protection Exception 

; Reserved ISRs
ISR_NOERRCODE 15 	; Reserved 
ISR_NOERRCODE 22 	; Reserved 
ISR_NOERRCODE 23 	; Reserved 
ISR_NOERRCODE 24 	; Reserved 
ISR_NOERRCODE 25 	; Reserved 
ISR_NOERRCODE 26 	; Reserved 
ISR_NOERRCODE 27 	; Reserved 
ISR_NOERRCODE 28 	; Reserved 
ISR_NOERRCODE 29 	; Reserved 
ISR_NOERRCODE 30 	; Reserved 
ISR_NOERRCODE 31 	; Reserved 


; Software-defined interrupts, placeholders until C function gives them usage 
ISR_NOERRCODE 32    ; Placeholder 
ISR_NOERRCODE 33    ; Placeholder  
ISR_NOERRCODE 34    ; Placeholder
ISR_NOERRCODE 35    ; Placeholder
ISR_NOERRCODE 36    ; Placeholder
ISR_NOERRCODE 37    ; Placeholder
ISR_NOERRCODE 38    ; Placeholder
ISR_NOERRCODE 39    ; Placeholder
ISR_NOERRCODE 40    ; Placeholder



; Define C function to handle ISRs
extern isr_handler


; Common stub, saves processor state, sets up for 
isr_common_stub: 
	pusha 		; save registers to stack	

	push ds  	; save segments to stack 
	push es 
	push fs 
	push gs 

	mov ax, 0x10  	; Load Kernel Data Segment descriptor
	mov ds, ax
	mov es, ax 
	mov fs, ax 
	mov gs, ax 

	mov eax, esp  	; push the stack pointer 
	push eax

	; call the C defined fault handler function 
	mov eax, isr_handler
	call eax 		; special call that preserves the `eip` register

	pop eax  		; pop off stack in reverse order 
	pop gs 
	pop fs 
	pop es 
	pop ds 
	popa 

	add esp, 8 		; Clean the pushed error code and ISR number 
	
	iret 
