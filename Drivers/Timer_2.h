#include <stdint.h>
typedef enum {
    TIMER_MODE_ONE_SHOT = 0x1,    // One-shot mode
    TIMER_MODE_PERIODIC = 0x2,     // Periodic mode
    TIMER_MODE_CAPTURE = 0x3      // Capture mode
} Timer_Mode_t;

typedef enum {
    TIMER_FG_32_BIT = 0x0,      // 32-bit timer configuration
    TIMER_FG_16_BIT = 0x4    
} Timer_Config_t;

typedef enum {
    TIMER_COUNT_DOWN = 0x0,
    TIMER_COUNT_UP = 0x1
} Timer_CountDir_t;
typedef enum {
    TIMER_PRESCALE_1 = 0x0,
    TIMER_PRESCALE_2 = 0x1,
} Timer_Prescale_t;

typedef enum {
    TIMER_INT_DISABLE = 0x0,
    TIMER_INT_ENABLE = 0x1
} Timer_InterruptState_t;

typedef enum {
    TIMER_DISABLE = 0x0,
    TIMER_ENABLE = 0x1
} Timer_State_t;

typedef struct {
    Timer_Mode_t mode;               // Timer mode
    Timer_Config_t config;           // Timer configuration (16/32 bit)
    Timer_CountDir_t countDir;       // Count direction
    Timer_Prescale_t prescale;       // Prescaler value
    Timer_InterruptState_t interrupt; // Interrupt enable/disable
    uint32_t loadValue;              // Timer load value
} Timer2_Config_t;

// Function prototypes 
     
extern Timer2_Config_t Timer2_InterruptConfig ;
extern Timer2_Config_t Timer2_DefaultConfig;
void Timer2_Init_T( Timer2_Config_t* config);
void Timer2_Start(void);
void Timer2_Stop(void);
void Timer2_SetLoadValue(uint32_t value);
void Timer2_EnableInterrupt(void);
void Timer2_DisableInterrupt(void);
void Delay100ms(unsigned long count);

