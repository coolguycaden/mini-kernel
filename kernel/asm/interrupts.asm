; Define a macro that takes one argument (%1)
%macro ISR_NOERRCODE 1
  global isr%1
  isr%1:
      cli

      ; Push dummy error code 
      push byte 0

      push byte %1
      jmp isr_common_stub
%endmacro

; Define a macro for ISRs that already push an error code (8, 10-14, etc.)
%macro ISR_ERRCODE 1
  global isr%1
  isr%1:
      cli
      
      ; No dummy error code push needed here
      push byte %1
      jmp isr_common_stub
%endmacro

; ISR WITH NO ErrCodes 
ISR_NOERRCODE 0     ; Divide Error 
ISR_NOERRCODE 1     ; Debug Exception
ISR_NOERRCODE 2     ; NMI interrupt 
ISR_NOERRCODE 3     ; Breakpoint
ISR_NOERRCODE 4     ; Overflow 
ISR_NOERRCODE 5     ; BOUND range exceeded 
ISR_NOERRCODE 6     ; Invalid opcode 
ISR_NOERRCODE 7     ; Device not available 
ISR_NOERRCODE 9     ; Coprocessor segment overrun 
ISR_NOERRCODE 16    ; x87 FPU Flopating Point Error 
ISR_NOERRCODE 18    ; Machine Check 
ISR_NOERRCODE 19    ; SIMD Floating Point Exception 
ISR_NOERRCODE 20    ; Virtualization Exception



; ISRs WITH ErrCodes 
ISR_ERRCODE 8
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_ERRCODE 17
ISR_ERRCODE 21


; Common stub, saves processor state, sets up for 
isr_common_stub: 
