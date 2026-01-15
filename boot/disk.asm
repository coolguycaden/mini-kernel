; disk.asm
; general purpose disk functions



; read a sector from disk
; used registers: CL, CH, DL, DH  
; input: DH - number of sectors to read (non zero) 
disk_load:
	mov ah, 0x02 	; BIOS read sector function 
	
    push dx         ; Save DH to pop later for number of sectors to read
       
    mov al, dh      ; Read DH sectors
	mov dl, 0 		; Read drive 0 
    mov ch, 0       ; Read cylinder 0 
	mov dh, 0       ; Read head 0 
    mov cl, 2       ; Read sector 2 (sector after boot sector) 

    
	int 0x13 		; BIOS INT to read 

	jc disk_error 	; jc jumps if carry flag was set (error) 

	pop dx          ; restore DX from stack  
    cmp dh, al      ; if AL (sectors read) != DH (sectors expected)
                    ; then display error message 
    jne disk_error

    ret 

disk_error:
	mov si, DISK_ERROR_MSG
	call print_string
	jmp $ 


; Global variable 
DISK_ERROR_MSG: db "Disk read error!", 0
