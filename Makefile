ASM_DIR = asm
BUILD_DIR = build

KERNEL_ASM = $(ASM_DIR)/basic_kernel.asm
KERNEL_BIN = $(BUILD_DIR)/basic_kernel.bin

BOOT_IMAGE = $(BUILD_DIR)/os_image.img

all: assemble run

assemble: 
	# Assemble bootloader
	nasm -f bin -o $(KERNEL_BIN) $(KERNEL_ASM)

	# Create 1.44MB floppy disk image
	dd if=/dev/zero of=$(BOOT_IMAGE) bs=512 count=2880

	# Write bootloader to boot sector (sector 1)
	dd if=$(KERNEL_BIN) of=$(BOOT_IMAGE) conv=notrunc

run:
	qemu-system-x86_64 -boot a -fda $(BOOT_IMAGE)

clean:
