; gdt.asm 
; Setting up the Global Descriptor Table in order 
; to raise from 16 bit real mode to 32 bit protected mode 
; I made this its own file due to its complexity 

gdt_start:

; the first entry in the GDBT *MUST* be a nul descriptor 
gdt_null:
    dd 0x0 
    dd 0x0 

; code segment descriptor 
; super complicated data structure, go to below link to read more
; https://wiki.osdev.org/Global_Descriptor_Table
gdt_code: 
    ; BASE = 0x0, LIMIT = 0xfffff
    ; BASE is segment base address
    ; LIMIT is segment limit
    
    ; 1st flags:
    ; present - privilege - descriptor type 
    ; values:
    ; 1       - 00        - 1
    ; => 1001b 

    ; type flags:
    ; code - conforming - readable - accessed 
    ; values:
    ; 1    - 0          - 1        - 0 
    ; => 1010b 

    ; 2nd flags:
    ; granularity - 32 bit default - 64 bit seg - AVL
    ; values:
    ; 1           - 1              - 0          - 0
    ; => 1100b 


    
    dw 0xffff       ; LIMIT (bits 0-15)
    dw 0x0          ; BASE (bits 0-15) 
    db 0x0          ; BASE (bits 16-23)  
    db 10011010b    ; 1st flags + type flags 
    db 11001111b    ; 2nd flags + Limit (bits 16-19) 
    db 0x0          ; BASE (bits 24-31) 



; data segment descriptor 
gdt_data:
    ; exact values as `gdt_code` except for the type flags
    ; type flags:
    ; code - expand down - writable - accessed
    ; values:
    ; 0    - 0           - 1        - 0
    ; => 0010b 

    dw 0xffff       ; LIMIT (bits 0-15)
    dw 0x0          ; BASE (bits 0-15) 
    db 0x0          ; BASE (bits 16-23)  
    db 10010010b    ; 1st flags + type flags 
    db 11001111b    ; 2nd flags + Limit (bits 16-19) 
    db 0x0          ; BASE (bits 24-31) 


; Define this label so the assembler can calculate
; the size of the GDT for the GDT descriptor below 
gdt_end: 


; GDT descriptor
gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; Size of GDT always less than one
                                ; of the true size 

    dd gdt_start                ; Start address of GDT 




switch_to_protected_mode:
	
	; Clear interrupts and ignore them (for now) 
	cli

	; Load the gdt descriptor with special
	; instruction 
	lgdt [gdt_descriptor] 

	mov eax, cr0 	; To switch to protected mode,
	or eax, 0x1 	; set the first bit of CR0, control register  
	mov cr0, eax 	; Update the control register 

	; Now, we are in 32-bit mode, but there is an issue: 
	; it is possible that the CPU pipelines instructions 
	; in a way that a now we could process 32-bit instructions
	; WITHOUT having the move into 32-bit mode complete all pipeline stages
	; To prevent ANY issues, we force the CPU to flush the pipeline
	; and we can do this by executing a far jump

	jmp CODE_SEG:init_protected_mode


[BITS 32] 
; Now, we are in 32-bit protected mode with no issues 
; Initialize registers and stack 
init_protected_mode:

	; Old segments in 16 bit real mode are useless now
	; so now point our segment registers to data selector
	; defined in the GDT 
	mov ax, DATA_SEG 		
	mov ds, ax
	mov ss, ax 
	mov es, ax 
	mov fs, ax
	mov gs, ax 

	mov ebp, 0x90000 	; Update stack position so it is at top
	mov esp, ebp 		; top of free space 

	call START_PROTECTED_MODE

; Define some handy constants for the GDT segment descriptor offsets , which
; are what segment registers must contain when in protected mode. For example ,
; when we set DS = 0 x10 in PM , the CPU knows that we mean it to use the
; segment described at offset 0 x10 ( i.e. 16 bytes ) in our GDT , which in our
; case is the DATA segment (0 x0 -> NULL ; 0 x08 -> CODE ; 0 x10 -> DATA )
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start


