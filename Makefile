ASSEMBLY_FOLDER = asm
BUILD_FOLDER = build

BOOTLOADER = $(ASSEMBLY_FOLDER)/stage1_bootloader.asm
BINARY = $(BUILD_FOLDER)/bootloader.bin
BOOT_IMAGE = $(BUILD_FOLDER)/os_image.img

assemble:
	# Assemble bootloader
	nasm -f bin -o myfirst.bin myfirst.asm

	

	nasm -f bin $(BOOTLOADER) -o $(BINARY)
	
	# Create 1.44MB floppy disk image
	dd if=/dev/zero of=$(BOOT_IMAGE) bs=512 count=2880

	# Write bootloader to boot sector (sector 1)
	dd if=$(BINARY) of=$(BOOT_IMAGE) conv=notrunc

	# Write test data to 512-byte sector (sector 2)
	echo -n ">> Sector 2 loaded!" | dd of=$(BOOT_IMAGE) bs=512 seek=1 conv=notrunc

run:
	qemu-system-x86_64 -boot a -fda $(BOOT_IMAGE)

clean:
