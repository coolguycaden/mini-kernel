#include "include/system.h"
#include "include/isrs.h"
#include "include/pit.h"

// keep track of how long system has been running 
int timer_ticks = 0; 

// Increment timer_ticks each time the timer fires 
// By default, this is at 18.222 Hz (IBM defined)
void timer_handler(struct InterruptStackFrame * stack) {
    timer_ticks++;
    
    // 18 ticks is a second 
    if (timer_ticks % 18) {
        print("A second has passed\n");
    }
}

void timer_setup() {
    irq_register_handler(0, timer_handler);
}
