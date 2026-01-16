# Connect to QEMU's local GDB server
target remote localhost:1234

# Load the kernel symbols 
symbol-file staging/kernel.o

# Set a breakpoint at the very start of the bootloader (0x7c00)
break *0x7c00

# Set a breakpoint at the start of kernel
break *0x9000

# Switch to assembly layout view automatically
layout asm

# Start running
continue
