## CadenOS Bootloader
A custom x86 bootloader and mini-kernel built from scratch.

## Project Description
A minimalist 16-bit x86 bootloader written in NASM Assembly that transitions into a 32-bit Protected Mode C kernel. The project currently boots from a simulated floppy disk, loads the kernel from disk to memory, sets up the Global Descriptor Table (GDT), and executes C code capable of direct VGA memory manipulation.

## Current Status
- **Bootloader**: Functional. Boots from MBR, loads kernel from disk, switches to 32-bit Protected Mode.
- **Kernel**: Minimal C kernel entry point established.
- **Build System**: Automated `Make` pipeline with QEMU emulation and GDB debugging support.

## To-do
### Completed
- [x] Boot from disk (Master Boot Record)
- [x] Load sectors from disk to memory
- [x] Implement 16-bit BIOS string and hex printing
- [x] Configure Global Descriptor Table (GDT)
- [x] Lift from 16-bit Real Mode to 32-bit Protected Mode
- [x] Hand off control from Assembly to C Kernel

### In Progress / Next Steps
- [ ] **VGA Driver**:
    - [ ] Implement cursor handling (hardware ports)
    - [ ] Implement screen scrolling
    - [ ] Full `printf` style support for the kernel
- [ ] **Input Driver**:
    - [ ] Write PS/2 Keyboard driver (scancode handling)
    - [ ] Create a keyboard buffer/queue
- [ ] **Kernel Utils**:
    - [ ] `memcpy`, `memset`, and memory helper functions
    - [ ] String manipulation (`strlen`, `strcmp`, `strcpy`)
- [ ] **Interrupts**:
    - [ ] Set up the Interrupt Descriptor Table (IDT)
    - [ ] Remap the PIC (Programmable Interrupt Controller)

## Goals
- Proficiency with Assembly and Low-level Architecture 
- Simple text editor + filesystem

## Stretch Goals 
- Number 1 most used kernel in the world
- Solve world hunger
- Found intergalatic empire focusing on human supremacy

## Resources

# Books
- [Writing a Simple Operating System from Scratch](https://angom.myweb.cs.uwindsor.ca/teaching/cs330/WritingOS.pdf)
- [Operating Systems: From 0 to 1](https://github.com/tuhdo/os01)

# Helpful Code
- `https://github.com/lukearend/x86-bootloader`
- `https://github.com/aayush598/basic-bootloader-assembly`
- `https://mikeos.sourceforge.net/write-your-own-os.html`

# Guides
- `https://wiki.osdev.org/Babystep1`
- `https://wiki.osdev.org/Creating_A_Shell`

# x86 Material
- `https://www.ctyme.com/intr/int.htm`
- `https://pastraiser.com/cpu/i8086/i8086_opcodes.html`
