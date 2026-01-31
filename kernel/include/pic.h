#ifndef KERNEL_PIC_H
#define KERNEL_PIC_H

// reference manual: https://www.intel.com/content/dam/www/public/us/en/documents/datasheets/7-series-chipset-pch-datasheet.pdf


// master / slave terminology will be replaced with
// controller / peripheral


/***************
 *
 * Controller PIC Defines 
 *
 ****************/ 

// Base address for controller PIC
#define PIC1_BASE_ADDRESS 	  0x20

// Initialization Command Word 1 Register 
#define PIC1_COMMAND          PIC1_BASE_ADDRESS 

// Initialization Command Word 2 Register 
#define PIC1_DATA             (PIC1_BASE_ADDRESS + 1)

// PIC1 should be remapped to 0x20 because Intel reserves the first
// 32 IRQs (0x1F) (interrupts 0-31), so we start at 0x20 
#define PIC1_REMAP_OFFSET     0x20



/***************
 *
 * Peripheral PIC Defines 
 *
 ****************/ 


// Base address for peripheral PIC 
#define PIC2_BASE_ADDRESS 	  0xA0 

// Initialization Command Word 1 Register (Peripheral)
#define PIC2_COMMAND          PIC2_BASE_ADDRESS 

// Initialization Command Word 2 Register 
#define PIC2_DATA             (PIC2_BASE_ADDRESS + 1) 

// PIC2 should always be 0ffset by 8 from PIC1
#define PIC2_REMAP_OFFSET     (PIC1_REMAP_OFFSET + 8)

// Intel standards state that bits 0-2 must be set to 0x02 
// to match the code broadcast by PIC1, the controller PIC
#define PIC2_ICW3_IDENTITY_CODE 0x02 


/***************
 *
 * General PIC Defines 
 *
 ****************/ 

// Starts the initialization sequence, in which the controller expects
// ICW2, ICW3, and ICW4 to be written to
#define PIC_ICW1_INIT 0x10 

// This bit must be set to 1; Intel standard dictates that ICW4 be used 
#define PIC_ICW1_ICW4_ENABLE 0x01 

// Bit 2 in ICW3 MUST be set to 1, because the interrupts 8-15 are cascaded
// onto the peripheral PIC
#define PIC_ICW3_CASCADE 0x04

// Bit 1 of ICW4 must be set to set the mode to 
// 8086 mode 
#define PIC_ICW4_8086_MODE 0x01 

// End-of-interrupt command code 
#define PIC_EOI 0x20 

// Initialization Command Word 4 Register 
#define PIC_ICW4 0x01

// Necessary to enable ICW2, ICW3, and ICW4 
#define PIC_ICW1_ENABLE 0x10 

// Set ICW1 to single (cascade) mode 
#define PIC_ICW1_MOD 0x02 

// Set to use 8086 mode  
#define PIC_ICW4_8086 0x01

// Set level trigger to edge mode 
#define PIC_ICW1_LEVEL 0x08 

// Select OCW3 for reading (IRR or ISR) 
#define PIC_OCW3_SELECT 0x08

// Read the Interrupt Request Register, which contains levels 
// requesting an interrupt to be acknolwedged
#define PIC_READ_IRR 0x0A

// Read the In-Service Register, contains priority levels
// that are being serviced 
#define PIC_READ_ISR 0x0B

#endif
