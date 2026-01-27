# DIRECTORY DEFINES 
BOOT_DIR   = boot
BUILD_DIR  = staging
KERNEL_DIR = kernel
DRIVER_DIR = drivers


# COMPILER AND LINKER FLAGS 
CXX = gcc 
COMPILE_FLAGS = -ffreestanding -m32 -g -fno-pie
LD_FLAGS 	  = -Ttext 0x1000 --oformat binary -m elf_i386 


# BOOTLOADER DEFINES 
BOOTLOADER_ASM = $(BOOT_DIR)/bootloader.asm 
BOOTLOADER_BIN = $(BUILD_DIR)/bootloader.bin
BOOTLOADER_OBJ = $(BUILD_DIR)/bootloader.o
BOOTLOADER_ELF = $(BUILD_DIR)/bootloader.elf
BOOT_IMAGE     = $(BUILD_DIR)/os_image.img

# KERNEL DEFINES 
KERNEL_ENTRY_ASM = $(KERNEL_DIR)/asm/kernel_entry.asm
KERNEL_ENTRY_ASM_OBJ = $(BUILD_DIR)/kernel_entry.o

# Find every .asm file in the directory
# Then, remove the KERNEL_ENTRY_ASM from that list because it MUST be linked first 
# Finally, create objects for all asms BESIDES kernel_entry.o 
KERNEL_ALL_ASM     		= $(wildcard $(KERNEL_DIR)/asm/*.asm)
KERNEL_OTHER_ASM   		= $(filter-out $(KERNEL_ENTRY_ASM), $(KERNEL_ALL_ASM))
KERNEL_OTHER_ASM_OBJS   = $(patsubst $(KERNEL_DIR)/asm/%.asm, $(BUILD_DIR)/%.o, $(KERNEL_OTHER_ASM))

KERNEL_BIN       = $(BUILD_DIR)/kernel.bin


# Find all kernel and driver .c files 
C_SOURCES = $(wildcard $(KERNEL_DIR)/*.c $(DRIVER_DIR)/*.c)  

# Find all kernel and driver .o files
C_OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(C_SOURCES)))

# KERNEL_ENTRY_ASM must be first in order to keep our kernel entry function
# in a static position 
ALL_KERNEL_OBJS = $(KERNEL_ENTRY_ASM_OBJ) $(KERNEL_OTHER_ASM_OBJ) $(C_OBJS)

# Where to look for .c files 
vpath %.c $(KERNEL_DIR) $(DRIVER_DIR)


# -----------------------------------
# TARGETS
# -----------------------------------

all: $(BOOT_IMAGE) run 

# Compile kernel .asm files -> .o 
$(KERNEL_ASM_OBJ): $(KERNEL_ASM)
	# make $(BUILD_DIR) if it does not exist 
	@mkdir -p $(BUILD_DIR)
	nasm $< -f elf -o $@

# Compile .c -> .o
$(BUILD_DIR)/%.o: %.c
	$(CXX) $(COMPILE_FLAGS) -c $< -o $@ 

# Compile .asm -> .o
$(BUILD_DIR)/%.o: $(KERNEL_DIR)/asm/%.asm
	@mkdir -p $(BUILD_DIR)
	nasm $< -f elf -o $@

# Link all kernel code together 
$(KERNEL_BIN): $(ALL_KERNEL_OBJS)
	ld -o $@ $(LD_FLAGS) $(ALL_KERNEL_OBJS)

# bootloader.asm -> .o 
$(BOOTLOADER_OBJ): $(BOOTLOADER_ASM)
	@mkdir -p $(BUILD_DIR)
	nasm $< -f elf -o $@

# Link bootloader.o and .elf, set start address to 
# 0x7C00 (code entry)
$(BOOTLOADER_ELF): $(BOOTLOADER_OBJ)
	ld -o $@ -Ttext 0x7c00 -m elf_i386 $<

# bootloader.elf -> .bin
$(BOOTLOADER_BIN): $(BOOTLOADER_ELF)
	objcopy -O binary $< $@


# Create boot image 
$(BOOT_IMAGE): $(BOOTLOADER_BIN) $(KERNEL_BIN)
	
	# Create an empty 1.44MB file
	dd if=/dev/zero of=$(BOOT_IMAGE) bs=512 count=2880

	# Write bootloader to Sector 0 (first 512 bytes)
	dd if=$(BOOTLOADER_BIN) of=$(BOOT_IMAGE) conv=notrunc

	# Write kernel to Sector 1 (skip first 512 bytes)
	dd if=$(KERNEL_BIN) of=$(BOOT_IMAGE) bs=512 seek=1 conv=notrunc



# -----------------------------------
# UTILS
# -----------------------------------

# KERNEL.ELF for DEBUGGING 
$(BUILD_DIR)/kernel.elf: $(ALL_KERNEL_OBJS)
	ld -o $@ -Ttext 0x1000 -m elf_i386 $(ALL_KERNEL_OBJS)


kernel_dump:
	objdump -b binary -m i386 -D $(KERNEL_BIN) > $(BUILD_DIR)/kernel.dump
	vim $(BUILD_DIR)/kernel.dump

boot_dump:
	objdump -b binary -m i386 -D $(BOOTLOADER_BIN) > $(BUILD_DIR)/boot.dump
	vim $(BUILD_DIR)/boot.dump

run:
	qemu-system-x86_64 -boot a -fda $(BOOT_IMAGE)

debug_start: $(BOOT_IMAGE)	$(BUILD_DIR)/kernel.elf
	qemu-system-x86_64 -s -S -boot a -fda $(BOOT_IMAGE) 

debug_connect: 
	gdb --tui -x debug/kernel.gdb

clean:
	rm -rf $(BUILD_DIR)/*

debug_vars:
	@echo "Source Files: $(C_SOURCES)"
	@echo "Object Files: $(C_OBJS)"
	@echo "ASMs: $(KERNEL_ASM)"
