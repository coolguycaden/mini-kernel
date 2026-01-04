[BITS 16]

start:
	mov ax, 0x07C0		; Set up 4K stack space after this bootloader
	add ax, 288		; (4096 + 512) / 16 bytes per paragraph
	mov ss, ax
	mov sp, 4096

	mov ax, 0x07C0		; Set data segment to where we're loaded
	mov ds, ax

.print_welcome
	mov si, text_welcome_string	; Put string position into SI
	call print_string	; Call our string-printing routine

    jmp main
 
main: 
.repeat:
    call print_console   
    call get_keystroke
    jmp .repeat
	   
%include "asm/print.asm"

text_welcome_string db 'Welcome to CadenOS!', 

times 510-($-$$) db 0	; Pad remainder of boot sector with 0s
dw 0xAA55		; The standard PC boot signature
