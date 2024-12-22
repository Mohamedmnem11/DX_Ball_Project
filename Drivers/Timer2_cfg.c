#include "Timer2_cfg.h"



// Default configuration for Timer2
Timer2_Config_t Timer2_DefaultConfig = {
    TIMER_MODE_PERIODIC,
    TIMER_FG_32_BIT,
    TIMER_COUNT_DOWN,
    TIMER_PRESCALE_1,
    TIMER_INT_DISABLE,
    8000000 - 1  // For 100ms at 80 MHz
};

// Configuration for Timer2 with interrupts
Timer2_Config_t Timer2_InterruptConfig = {
    TIMER_MODE_PERIODIC,
    TIMER_FG_32_BIT,
    TIMER_COUNT_DOWN,
    TIMER_PRESCALE_1,
    TIMER_INT_ENABLE,
    8000000 - 1  // For 100ms at 80 MHz
};

void Timer2_Init(){
	Timer2_Init_T(&Timer2_InterruptConfig);

}
