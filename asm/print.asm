; print.asm 
; Reusable BIOS printing functions 

[BITS 16]


get_keystroke:
.repeat:
    
    ; Get Keystroke Interrupt
    mov ah, 0x00       
    int 0x16
    
    ; 0x0D = carraige return (enter)
    cmp al, 0x0D      
    je .done
    
    call print_char
    jmp .repeat

.done:
    call print_char
    ret




newline_and_carriage_ret:
    mov si, text_newline_character
    call print_string

    mov si, text_carriage_ret_character
    call print_string

    ret
    
    

print_console:
    call newline_and_carriage_ret

    mov si, text_console_character
    call print_string

    ret




; Prints character stored in input, AL 
print_char:

    mov ah, 0x0E
    int 0x10
    ret


; Output string in SI to screen
print_string:			
	mov ah, 0x0E

.repeat:
	lodsb			; Get character from string
	cmp al, 0
	je .done		; If char is zero, end of string
	call print_char
    jmp .repeat

.done:
	ret

text_newline_character db 10, 0
text_carriage_ret_character db 13, 0
text_console_character db '>>> ', 0
buffer_user_text db 64 dup 0
