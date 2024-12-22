#include "Timer_2.h"
#include "Game/tm4c123gh6pm.h"

// Timer2 initialization with configuration structure
void Timer2_Init_T(Timer2_Config_t* config) {
    unsigned long volatile delay;

    SYSCTL_RCGCTIMER_R |= (1 << 2);
    delay = SYSCTL_RCGCTIMER_R;  
    TIMER2_CTL_R = 0;
    TIMER2_CFG_R = config->config;
    TIMER2_TAMR_R = config->mode;
    if(config->countDir == TIMER_COUNT_UP) {
        TIMER2_TAMR_R |= (1 << 4);
    }
    TIMER2_TAILR_R = config->loadValue;
    TIMER2_TAPR_R = config->prescale;
    TIMER2_ICR_R = 0x1;
    if(config->interrupt == TIMER_INT_ENABLE) {
        TIMER2_IMR_R = 0x1;
        
        NVIC_EN0_R = 1 << 23;  
    } else {
        TIMER2_IMR_R = 0x0;
    }
}

void Timer2_Start(void) {
    TIMER2_CTL_R |= 0x1;
}

void Timer2_Stop(void) {
    TIMER2_CTL_R &= ~0x1;
}

void Timer2_SetLoadValue(uint32_t value) {
    TIMER2_TAILR_R = value - 1;
}

void Timer2_EnableInterrupt(void) {
    TIMER2_IMR_R |= 0x1;
    NVIC_EN0_R = 1 << 23;
}

void Timer2_DisableInterrupt(void) {
    TIMER2_IMR_R &= ~0x1;
}


void Delay100ms(unsigned long count) {
    Timer2_Config_t delayConfig = Timer2_DefaultConfig;
    Timer2_Init_T(&delayConfig);
    Timer2_Start();

    while(count > 0) {
        while((TIMER2_RIS_R & 0x1) == 0) {
           
        }
        TIMER2_ICR_R = 0x1;
        count--;
    }
    
    Timer2_Stop();
}

// Interrupt handler
void Timer2A_Handler(void) {
    TIMER2_ICR_R = 0x1;
}
