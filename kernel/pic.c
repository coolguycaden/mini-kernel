#include "include/system.h"
#include "include/pic.h"



// controller_offset - vector offset for controller PIC
// offset becomes controller_offset...controller_offset+7
//
// peripheral_offset - same as controller_offset 
// offset => peripheral_offset...peripheral_offset+7
void pic_remap(int controller_offset, int peripheral_offset) {
	
	// start initialization sequence in cascade mode, must present ICW4 enable bit
    // use io_wait for compatibility for older PICs (speed compatibility)
	port_byte_write(PIC1_COMMAND, PIC_ICW1_INIT | PIC_ICW1_ICW4_ENABLE);
	io_wait();	
    port_byte_write(PIC2_COMMAND, PIC_ICW1_INIT | PIC_ICW1_ICW4_ENABLE);
	io_wait();	

    // now, we write the offsets to the PIC ICW2
    port_byte_write(PIC1_DATA, controller_offset);
    io_wait(); 
    port_byte_write(PIC2_DATA, peripheral_offset);
    io_wait(); 

    // as defined by Intel standard, see comments in "pic.h" 
    port_byte_write(PIC1_DATA, PIC_ICW3_CASCADE);
    io_wait();
    port_byte_write(PIC2_DATA, PIC2_ICW3_IDENTITY_CODE);
    io_wait(); 

    // set both PIC's ICW4 to 8086 mode 
    port_byte_write(PIC1_DATA, PIC_ICW4_8086_MODE);
    io_wait(); 
    port_byte_write(PIC2_DATA, PIC_ICW4_8086_MODE);
    io_wait();

    // now unmask all interrupts 
    port_byte_write(PIC1_DATA, 0);
    port_byte_write(PIC2_DATA, 0);
}


void pic_setup() {
    pic_remap(PIC1_REMAP_OFFSET, PIC2_REMAP_OFFSET);
}

// Disable PIC, usually done to use the APIC instead 
void pic_disable() {
	port_byte_write(PIC1_COMMAND, 0xFF);
	port_byte_write(PIC2_COMMAND, 0xFF);
}


// Sends end-of-interrupt command code  
void pic_send_eoi(unsigned char irq){
	
	// if IRQ comes from the peripheral PIC, then we must
	// send command to BOTH PIC 
	if(irq >= 8) {
		port_byte_write(PIC2_COMMAND, PIC_EOI);
	} 

	port_byte_write(PIC1_COMMAND, PIC_EOI);
}


// credit to https://wiki.osdev.org/8259_PIC
void pic_set_irq_mask(unsigned char IRQline) {
    unsigned short port;
    unsigned char value;

    // Controller PIC handles IRQ 0-7, 
    // Peripheral PIC handles IRQ 8-15
    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }

    value = port_byte_read(port) | (1 << IRQline);
    port_byte_write(port, value);
}

// credit to https://wiki.osdev.org/8259_PIC
void pic_clear_irq_mask(unsigned char IRQline) {
    unsigned short port;
    unsigned char value;

    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }

    value = port_byte_read(port) & ~(1 << IRQline);
    port_byte_write(port, value);
}

// Helper function to set both PIC1/2's OCW3 to requested
// register and then read from it 
static unsigned short __pic_read_ocw3_reg(int reg) {
    
    port_byte_write(PIC1_COMMAND, reg);
    port_byte_write(PIC2_COMMAND, reg);
    return (port_byte_read(PIC2_COMMAND) << 8) | port_byte_read(PIC1_COMMAND);
}

// Read value of combined PIC1/2's Interrupt Request Register (IRR) 
unsigned short pic_get_irr() {
    
    return __pic_read_ocw3_reg(PIC_READ_ISR);
}

unsigned short pic_get_isr() {
    
    return __pic_read_ocw3_reg(PIC_READ_IRR);
}
