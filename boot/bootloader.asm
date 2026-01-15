[BITS 16]
[ORG 0x7c00]

section .text
    global _start

_start:
    mov [BOOT_DRIVE], dl 
    
    mov bp, 0x8000
    mov sp, bp 

    mov bx, 0x9000
    mov dh, 5
    mov dl, [BOOT_DRIVE] 
    call disk_load

.print_welcome:
	mov si, text_welcome_string	    ; Put string position into SI
	call print_string	            ; Call print 

    jmp main
	 
main: 
.repeat:
    call print_console
    call get_keystroke
    jmp .repeat
	   


%include "boot/print.asm"
%include "boot/disk.asm"

BOOT_DRIVE: db 0 

text_welcome_string db 'Welcome to CadenBoot!', 0

times 510-($-$$) db 0	; Pad remainder of boot sector with 0s
dw 0xAA55		        ; The standard PC boot signature
