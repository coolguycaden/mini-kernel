[BITS 16]

section .text
    global _start

_start:
	mov ax, 0x07C0		; Set up 4K stack space after this bootloader
	add ax, 288		; (4096 + 512) / 16 bytes per paragraph
	mov ss, ax
	mov sp, 4096

	mov ax, 0x07C0		; Set data segment to where we're loaded
	mov ds, ax

.print_welcome:
	mov si, text_welcome_string	; Put string position into SI
	call print_string	; Call our string-printing routine

    jmp main
	 
main: 
.repeat:
    call print_console
    call newline_and_carriage_ret
    call get_keystroke
    jmp .repeat
	   

text_welcome_string db 'Welcome to CadenBoot!', 0

%include "boot/print.asm"

times 510-($-$$) db 0	; Pad remainder of boot sector with 0s
dw 0xAA55		; The standard PC boot signature

