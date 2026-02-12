## CadenOS Mini-kernel + Bootloader
A custom x86 bootloader and mini-kernel built from scratch.

## Project Description
A minimalist 16-bit x86 bootloader written in NASM Assembly that transitions into a 32-bit Protected Mode C kernel. The project currently boots from a simulated floppy disk, loads the kernel from disk to memory, and sets up the Global Descriptor Table (GDT).
The kernel features direct VGA memory manipulation, a fully functional Interrupt Descriptor Table (IDT) with Programmable Interrupt Controller (PIC) remapping, and a robust architecture for handling both CPU exceptions and hardware interrupts.

## Current Status
- **Bootloader**: Functional. Boots from MBR, loads kernel from disk, switches to 32-bit Protected Mode.
- **Kernel**: Functional C kernel with VGA text driver, IDT/ISR interrupt handling, and basic keyboard (IRQ1) integration.
- **Build System**: Automated `Make` pipeline with QEMU emulation and GDB debugging support.

## To-do
### Completed
- [x] Boot from disk, raise from 16-bit to 32-bit mode 
- [x] Load C Kernel into memory
- [x] Basic screen printing, scrolling
- [x] Basic kernel utils (`memcpy`, `memset`, etc)
- [x] Setup Interrupt Descriptor Table 
- [x] Remap'd PIC 
- [x] Implement basic keyboard driver 

### In Progress / Next Steps
- [x] **Input Driver**:
    - [x] Implement Scancode ASCII translation 
    - [ ] Create a keyboard ring buffer/queue
    - [ ] Handle key release and modifier keys (Shift/Ctrl)
- [ ] Shell / Interaction:
    - [ ] Basic command pasring 
    - [ ] Backspace support

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
- [x86 Bootloader](https://github.com/lukearend/x86-bootloader)
- [Another x86 Bootloader](https://github.com/aayush598/basic-bootloader-assembly)
- [Simple ASM OS](https://mikeos.sourceforge.net/write-your-own-os.html)

# Guides
- [OS Dev Wiki](https://wiki.osdev.org/Expanded_Main_Page)
- [Bran's Kernel Development Guide](http://www.osdever.net/bkerndev/index.php)

# Intel Material
- [BIOS Interrupts](https://www.ctyme.com/intr/int.htm)
- [8086 Opcodes](https://pastraiser.com/cpu/i8086/i8086_opcodes.html)
- [Intel 7 Series Chipset Datasheet](https://www.intel.com/content/dam/www/public/us/en/documents/datasheets/7-series-chipset-pch-datasheet.pdf)
- [Intel Software Developer Guide](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html)
