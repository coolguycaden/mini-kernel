#include "include/system.h"
#include "include/pit.h"

void pit_setup_rate_generator(int clock_hz) {

    unsigned char control_byte = 0;

    control_byte |= PIT_SELECT_COUNTER_0  
        | PIT_WR_WORD 
        | PIT_MODE_3_SQUARE_GENERATOR
        | PIT_BINARY_COUNTER_TYPE;

    
    // Update command register 
    port_byte_write(PIT_COMMAND, control_byte);
    
    int divisor = PIT_BASE_HZ / clock_hz;  
    
    // PIT_WR_WORD demands we send low byte first 
    port_byte_write(PIT_CHANNEL_0_DATA, divisor & 0xFF);
    port_byte_write(PIT_CHANNEL_0_DATA, divisor >> 8);
}
