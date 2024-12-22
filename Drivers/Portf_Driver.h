#include <stdint.h>

typedef enum Gpio_Return_e{
	GPIO_RET_OK,
	GPIO_RET_NOT_OK
}Gpio_Return_t;
typedef enum  GPIO_Dir{
    PORTF_DIR_INPUT = 0,
    PORTF_DIR_OUTPUT = 1
} PortF_DirConfig_t;

typedef enum GPIO_Altr {
    PORTF_FUNC_GPIO = 0,
    PORTF_FUNC_ALTERNATE = 1
} PortF_FuncConfig_t;


typedef enum GPIO_DIGITAL_ANALOG_SELECT
{
	DIGITAL,
	ANALOG

}GPIO_DIGITAL_ANALOG_SELECT_t;
typedef enum GPIO_PullUpR{
    PORTF_PULLUP_DISABLE = 0,
    PORTF_PULLUP_ENABLE = 1
} PortF_PullupConfig_t;

typedef enum GPIO_INT_SEN {
    PORTF_INT_EDGE = 0,
    PORTF_INT_LEVEL = 1
} PortF_IntSensConfig_t;

typedef enum PORTF_INT_MODE {
    PORTF_INT_SINGLE_EDGE = 0,
    PORTF_INT_BOTH_EDGES = 1
} PortF_IntEdgeConfig_t;

typedef enum  PORTF_INT_Event{
    PORTF_INT_FALLING = 0,
    PORTF_INT_RISING = 1
} PortF_IntEventConfig_t;
typedef enum GPIO_enable{
	ENABLE =0,
	DISABLE =1

} GPIO_enable_t;
typedef enum GPIO_CommitConfig_e {
    ALLOW_CHANGES =1,    
    DONOT_ALLOW_CHANGES = 0,    
} GPIO_CommitConfig_t;

typedef enum PORTF_INT_Mask{
    PORTF_INT_MASK_DISABLE = 0,
    PORTF_INT_MASK_ENABLE = 1
} PortF_IntMaskConfig_t;

typedef enum PortFpins{
    PORTF_PIN0 = (1 << 0),    // SW2
    PORTF_PIN1 = (1 << 1),    // RED LED
    PORTF_PIN2 = (1 << 2),    // BLUE LED
    PORTF_PIN3 = (1 << 3),    // GREEN LED
    PORTF_PIN4 = (1 << 4)     // SW1
} PortF_PinConfig_t;
typedef enum {
    GPIO_INT_PRIORITY_0 = 0,  
    GPIO_INT_PRIORITY_1 = 1,
    GPIO_INT_PRIORITY_2 = 2,
    GPIO_INT_PRIORITY_3 = 3,
    GPIO_INT_PRIORITY_4 = 4,
    GPIO_INT_PRIORITY_5 = 5,
    GPIO_INT_PRIORITY_6 = 6,
    GPIO_INT_PRIORITY_7 = 7      
} GPIO_InterruptPriority_t;

// Enum for NVIC registers selection
typedef enum {
    NVIC_PRI0 = 0,
    NVIC_PRI1,
    NVIC_PRI2,
    NVIC_PRI3,
    NVIC_PRI4,
    NVIC_PRI5,
    NVIC_PRI6,
    NVIC_PRI7
} NVIC_PRIx_Register_t;

typedef struct {
    uint8_t interruptNumber;     
    NVIC_PRIx_Register_t priRegister;  
    uint8_t priorityShift;       
    GPIO_InterruptPriority_t priority;  
          
} InterruptConfig_t;

typedef enum {
    NVIC_PORT_F_INT = 30     // Port F interrupt number in NVIC
} NVIC_InterruptNumber_t;


typedef struct{
GPIO_DIGITAL_ANALOG_SELECT_t mode;
	GPIO_CommitConfig_t allow;
	PortF_DirConfig_t  direction;
	PortF_FuncConfig_t function;
	PortF_PullupConfig_t pullup;
	PortF_IntSensConfig_t intsen;
	PortF_IntEdgeConfig_t edge;
	PortF_IntEventConfig_t event;
	PortF_IntMaskConfig_t mask;
} PinConfig_t;
extern PinConfig_t PortF_PinConfigs[] ;
Gpio_Return_t PORTF_init(PinConfig_t PortF_PinConfigs[] );
Gpio_Return_t GPIO_ConfigureInterrupt(InterruptConfig_t* config);
Gpio_Return_t GPIO_SetCommitReg(PortF_PinConfig_t pins, GPIO_CommitConfig_t commitState);
Gpio_Return_t GPIO_SetPinDirection(PortF_PinConfig_t pins, PortF_DirConfig_t direction);
Gpio_Return_t GPIO_SetAlternateFunction(PortF_PinConfig_t pins, PortF_FuncConfig_t function);
Gpio_Return_t GPIO_SetDigitalAnalogSelect(PortF_PinConfig_t pins, GPIO_DIGITAL_ANALOG_SELECT_t select);
Gpio_Return_t GPIO_SetPullUp(PortF_PinConfig_t pins, PortF_PullupConfig_t pullup);
Gpio_Return_t GPIO_SetInterruptSensitivity(PortF_PinConfig_t pins, PortF_IntSensConfig_t sensitivity);
Gpio_Return_t GPIO_SetInterruptEdgeMode(PortF_PinConfig_t pins, PortF_IntEdgeConfig_t edgeMode);
Gpio_Return_t GPIO_SetInterruptEvent(PortF_PinConfig_t pins, PortF_IntEventConfig_t event);
Gpio_Return_t GPIO_SetInterruptMask(PortF_PinConfig_t pins, PortF_IntMaskConfig_t mask);
Gpio_Return_t GPIO_ClearInterrupt(PortF_PinConfig_t pins);
void GPIO_PortF_Init(void);
