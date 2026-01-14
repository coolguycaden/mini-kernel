BOOT_DIR = boot
BUILD_DIR = staging

BOOTLOADER_ASM = $(BOOT_DIR)/bootloader.asm
BOOTLOADER_BIN = $(BUILD_DIR)/bootloader.bin

BOOT_IMAGE = $(BUILD_DIR)/os_image.img

all: assemble run

assemble: 
	# Assemble bootloader
	nasm $(BOOTLOADER_ASM) -f bin -o $(BOOTLOADER_BIN)

	# Create 1.44MB floppy disk image
	dd if=/dev/zero of=$(BOOT_IMAGE) bs=512 count=2880

	# Write bootloader to boot sector (sector 1)
	dd if=$(BOOTLOADER_BIN) of=$(BOOT_IMAGE) conv=notrunc

run:
	qemu-system-x86_64 -boot a -fda $(BOOT_IMAGE)

raw: 
	od -t x1 -A n $(BOOTLOADER_BIN)

debug:
	qemu-system-x86_64 -s -S -boot a -fda $(BOOT_IMAGE)

connect:
	gdb --ex "target remote localhost:1234"
