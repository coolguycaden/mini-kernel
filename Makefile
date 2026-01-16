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
BOOT_IMAGE     = $(BUILD_DIR)/os_image.img

# KERNEL DEFINES 
KERNEL_ENTRY_ASM = $(KERNEL_DIR)/asm/kernel_entry.asm
KERNEL_ENTRY_OBJ = $(BUILD_DIR)/kernel_entry.o
KERNEL_BIN 		 = $(BUILD_DIR)/kernel.bin

# Find all kernel and driver .c files 
C_SOURCES = $(wildcard $(KERNEL_DIR)/*.c $(DRIVER_DIR)/*.c)  

# Find all kernel and driver .o files
# .o files are stored in $(BUILD_DIR), so we look there 
C_OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(C_SOURCES)))

# Important that `kernel_entry.o` is first,
# it is in the name after all 
ALL_KERNEL_OBJS = $(KERNEL_ENTRY_OBJ) $(C_OBJS)

# Tell Make where to look for .c files 
vpath %.c $(KERNEL_DIR) $(DRIVER_DIR)


# -----------------------------------
# TARGETS
# -----------------------------------

all: $(BOOT_IMAGE) run 

# Compile kernel_entry.asm -> .o 
$(KERNEL_ENTRY_OBJ): $(KERNEL_ENTRY_ASM)
	# make $(BUILD_DIR) if it does not exist 
	@mkdir -p $(BUILD_DIR)
	nasm $^ -f elf -o $@

# Compile .c -> .o
$(BUILD_DIR)/%.o: %.c
	$(CXX) $(COMPILE_FLAGS) -c $< -o $@ 

# Link everything together 
$(KERNEL_BIN): $(ALL_KERNEL_OBJS)
	ld -o $@ $(LD_FLAGS) $(ALL_KERNEL_OBJS)

# Assemble bootloader binary
$(BOOTLOADER_BIN): $(BOOTLOADER_ASM)
	nasm $< -f bin -o $@ 

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


dump:
	objdump -b binary -m i386 -D $(BOOTLOADER_BIN) > $(BUILD_DIR)/boot.dump
	objdump -b binary -m i386 -D $(KERNEL_BIN) > $(BUILD_DIR)/kernel.dump

run:
	qemu-system-x86_64 -boot a -fda $(BOOT_IMAGE)

debug_start: $(BOOT_IMAGE)	
	qemu-system-x86_64 -s -S -boot a -fda $(BOOT_IMAGE) 

debug_connect: 
	gdb -x debug/debug.gdb

clean:
	rm -rf $(BUILD_DIR)/*

debug_vars:
	@echo "Source Files: $(C_SOURCES)"
	@echo "Object Files: $(C_OBJS)"
