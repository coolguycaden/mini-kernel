#ifndef KERNEL_PIT_H
#define KERNEL_PIT_H

// PIT 8 bit registers for each channel 
#define PIT_CHANNEL_0_DATA 0x40 
#define PIT_CHANNEL_1_DATA 0x41 
#define PIT_CHANNEL_2_DATA 0x42

#define PIT_COMMAND 0x43




#define PIT_SELECT_COUNTER_0 0x00
#define PIT_SELECT_COUNTER_1 0x40  // Counter 1 is deprecated or
                            // not implemented in modern times
#define PIT_SELECT_COUNTER_2 0x80 

// Read / write word (2bytes), least significant first
// and then most significant byte 
#define PIT_WR_WORD 0x30 

// Frequency divider mode, periodic mode that
// starts high, and goes low for one cycle, high again, repeat 
#define PIT_MODE_2_RATE_GENERATOR  0x04 

// Similiar to RATE_GENERATOR, however the OUT will start high,
// and then once half the count has expired, OUT will be low for remainder
// of the count 
#define PIT_MODE_3_SQUARE_GENERATOR 0x06 

// 2 counter types = binary (2^16) or 
// Binary Coded Decimal = 10^4 
#define PIT_BINARY_COUNTER_TYPE 0x00
#define PIT_BCD_COUNTER_TYPE 0x01 

// 1.193182 MHz base signal 
#define PIT_BASE_HZ 1193182


extern void pit_setup_rate_generator(int clock_hz);

#endif 
