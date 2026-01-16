; print_pm.asm
; print functions altered from 16 real mode to 32 bit protected mode

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

; Print null-terminated pointed by ESX 
print_string_pm:

	pusha 
	mov edx, VIDEO_MEMORY 

.repeat:
	mov al, [esi]
	mov ah, WHITE_ON_BLACK

	cmp al, 0
	je .done

	mov [edx], ax 

	add esi, 1 
	add edx, 2 



	jmp .repeat 
.done:
	popa
	ret 
