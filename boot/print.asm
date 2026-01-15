; print.asm 
; Reusable BIOS printing functions 

[BITS 16]

; In the name, get keystroke from user input
get_keystroke:
.repeat:
    
    mov ah, 0x00        ; Get Keystroke Interrupt
    int 0x16
    
    cmp al, 0x0D        ; 0x0D = carraige return (enter)
    je .done
    
    call print_char
    jmp .repeat

.done:
    call print_char
    ret



; Simple routine to print new line to screen 
; and return cursor to beginning of line
newline_and_carriage_ret:
	pusha

	mov si, text_newline_character    	; Print newline character
    call print_string

    mov si, text_carriage_ret_character ; Print carriage return, cursor set to beginning of newline
    call print_string

	popa 
    ret
    
    
; Simple routine to echo what the user types to scren
print_console: 	
	pusha
	
	call newline_and_carriage_ret 	 

    mov si, text_console_character 	; print default console text
    call print_string

	popa
    ret

; Prints character stored in input, AL 
print_char:     

    mov ah, 0x0E
    int 0x10
    ret

; Output string in SI to screen
print_string:      
	pusha           ; Save all registers to stack
	mov ah, 0x0E

.repeat:
	lodsb			; Get character from string
	cmp al, 0
	je .done		; If char is zero, end of string
	call print_char
    jmp .repeat

.done:
    popa            ; Return registers to values before call
	ret


; Print 16-bit value stored in DX as hex to screen 
print_hex:
   mov si, HEXA_PREFIX
   call print_string 

  
   mov cl, 4
   mov [LOOP_AMOUNT], cl

.repeat:
        

    mov cl, [LOOP_AMOUNT]
    cmp cl, 1 
    jl .done 

    ; decrement loop count and store it 
    sub cl, 1            
    mov [LOOP_AMOUNT], cl 

    ; shift amount (AL) = counter * 4
    ; pattern = 12, 8, 4, 0
    mov al, 4
    mul cl 
    mov cl, al
    
    mov ax, dx    ; take copy of data (DX) into AX 
    shr ax, cl    ; shift copy data right by CL

    ; AND bottom 4 bits of AX to get the value of the nibble 
    and ax, 0x0F
    
    ; easy hack to turn numbers into their ASCII equivalent using a known ASCII value
    ; so just jump to handle 0-9, and a-f (10-15)
    cmp ax, 9 
    jle .zero_through_nine
    jmp .ten_through_fiften

   
.zero_through_nine:
    ; values 0-9 can be turned into ASCII 
    ; just by adding the ASCII of '0'
    add ax, '0'
    
    jmp .char_to_screen

.ten_through_fiften:
    ; values 10-15 can be turned into ASCII 
    ; just by adding 55 (10 + 55 = 65 = 'A') 
    add ax, 55 
     
    
    jmp .char_to_screen

.char_to_screen: 
    
    ; print_char takes character input as AL
    ; char is already loaded into AX, so call routine  
    call print_char    
    jmp .repeat  


.done: 
    
    ret 
    
    HEXA_PREFIX: db "0x", 0 
    SHIFT_AMOUNT: db 0 
    LOOP_AMOUNT: db 0 

text_newline_character db 10, 0
text_carriage_ret_character db 13, 0
text_console_character db '>>> ', 0
