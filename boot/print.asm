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
    
    push bp         ; Save caller stackframe  
    mov bp, sp      ; set stack up 
    
    sub sp, 5       ; allocate 5 bytes for stack 
                    ; 4 bytes for the 4 characters from DX   - [rbp - 4] : [rbp - 1] 
                    ; 1 byte to hold calculated shift amount - [rbp - 5]
    


    mov cl, 4 		; Number of times to loop  
    

.repeat:

	cmp cl, 1  		; check if loop is finished 
	jl .done
    
    sub cl, 1       ; decrement counter 

    ; shift amount (AL) = counter * 4
    ; pattern = 12, 8, 4, 0
    mov al, 4
    mul cl 
    
    mov si, bp      
    sub si, 5       ; calculate offset to access our "shift amount" variable on the stack 
    mov [si], al    ; move calculated shift amount into correct address on stack 
    
    
    push cx         
    mov ax, dx       
    mov cl, [si]    ; store calculated shift into cl 
    shr ax, cl      ; shift ax right by cl 
    pop cx          

    ; AND bottom 4 bits of AX to get the value of the nibble 
    and ax, 0x0F
    
    ; easy hack to turn numbers into their ASCII equivalent using a known ASCII value
    cmp ax, 9 
    jl .zero_through_nine
    jmp .ten_through_fiften

   
.zero_through_nine:
    ; values zero through nine can be turned into ASCII 
    ; just by adding the ASCII of '0'
    
    add ax, '0'
    
    jmp .save_value

.ten_through_fiften:
    ; values zero through nine can be turned into ASCII 
    ; just by adding the ASCII of 'A' (you can also change it to 'a') 
    add ax, 'A'
     

    jmp .save_value

.save_value:
    mov di, bp      ; copy BP offset to DI 
    sub di, cx      ; subtract DI from counter to get next index to store  
                    ; ASCII character that was just calculated

   
    mov [di], ax    ; save ASCII character in the 4-byte array that was created 
    jmp .repeat  


.done: 

    mov si, HEXA_PREFIX
    call print_string 
    
    sub di, 3       ; substract 3 from DI to print entire 4-byte array = BP - 3
    mov si, di      ; load DI into SI to be printed 
    call print_string 
    
    pop bp
    ret 
    
    HEX_OUT db "done", 0
    HEXA_PREFIX db "0x", 0 

text_newline_character db 10, 0
text_carriage_ret_character db 13, 0
text_console_character db '>>> ', 0
