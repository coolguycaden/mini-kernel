[BITS 16]
[ORG 0x7c00]

KERNEL_OFFSET equ 0x1000

_boot:
    mov [BOOT_DRIVE], dl 
    
    mov bp, 0x9000
    mov sp, bp 
	
	mov si, WELCOME_REAL_MODE  	; celebrate 16-bit boot
	call print_string 
	
	call load_kernel 			; load kernel 

	; we will NOT return from this call 
	call switch_to_protected_mode
	
	jmp $

%include "boot/print.asm"
%include "boot/disk.asm"
%include "boot/gdt.asm" 
%include "boot/print_pm.asm"

[BITS 16]

load_kernel:
	mov si, WELCOME_LOADING_KERNEL
	call print_string 

	mov bx, KERNEL_OFFSET 	; Load first 15 sectors after boot sector
	mov dh, 15 				; to the ADDRESS at KERNEL_OFFSET 
	mov dl, [BOOT_DRIVE]
	call disk_load 

	ret 

[BITS 32] 
START_PROTECTED_MODE: 
	
	mov esi, WELCOME_PROT_MODE
	call print_string_pm

	call KERNEL_OFFSET
	
	mov esi, WELCOME_RETURN
	call print_string_pm

	jmp $


BOOT_DRIVE: db 0 
WELCOME_REAL_MODE: db "Booted in 16-bit Real Mode!", 0
WELCOME_PROT_MODE: db "Successfully landed in 32-bit Protected Mode", 0
WELCOME_LOADING_KERNEL: db "Loading kernel!", 0
WELCOME_RETURN: db "Returned!", 0

times 510-($-$$) db 0	; Pad remainder of boot sector with 0s
dw 0xAA55		        ; The standard PC boot signature
