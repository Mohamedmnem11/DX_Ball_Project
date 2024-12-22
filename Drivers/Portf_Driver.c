#include "Drivers/Portf_Driver.h"
#include "Game/tm4c123gh6pm.h"

Gpio_Return_t GPIO_SetPinDirection(PortF_PinConfig_t pins, PortF_DirConfig_t direction) {
    if(direction == PORTF_DIR_OUTPUT) {
        GPIO_PORTF_DIR_R |= pins;
    } else {
        GPIO_PORTF_DIR_R &= ~pins;
    }
    return GPIO_RET_OK;
}

Gpio_Return_t GPIO_SetAlternateFunction(PortF_PinConfig_t pins, PortF_FuncConfig_t function) {
    if(function == PORTF_FUNC_ALTERNATE) {
        GPIO_PORTF_AFSEL_R |= pins;
    } else {
        GPIO_PORTF_AFSEL_R &= ~pins;
    }
    return GPIO_RET_OK;
}



Gpio_Return_t GPIO_SetDigitalAnalogSelect(PortF_PinConfig_t pins, GPIO_DIGITAL_ANALOG_SELECT_t select) {
    if(select == DIGITAL) {
        GPIO_PORTF_DEN_R |= pins;
        GPIO_PORTF_AMSEL_R &= ~pins;
    } else {
        GPIO_PORTF_DEN_R &= ~pins;
        GPIO_PORTF_AMSEL_R |= pins;
    }
    return GPIO_RET_OK;
}

Gpio_Return_t GPIO_SetPullUp(PortF_PinConfig_t pins, PortF_PullupConfig_t pullup) {
    if(pullup == PORTF_PULLUP_ENABLE) {
        GPIO_PORTF_PUR_R |= pins;
    } else {
        GPIO_PORTF_PUR_R &= ~pins;
    }
    return GPIO_RET_OK;
}

Gpio_Return_t GPIO_SetInterruptSensitivity(PortF_PinConfig_t pins, PortF_IntSensConfig_t sensitivity) {
    if(sensitivity == PORTF_INT_LEVEL) {
        GPIO_PORTF_IS_R |= pins;
    } else {
        GPIO_PORTF_IS_R &= ~pins;
    }
    return GPIO_RET_OK;
}

Gpio_Return_t GPIO_SetInterruptEdgeMode(PortF_PinConfig_t pins, PortF_IntEdgeConfig_t edgeMode) {
    if(edgeMode == PORTF_INT_BOTH_EDGES) {
        GPIO_PORTF_IBE_R |= pins;
    } else {
        GPIO_PORTF_IBE_R &= ~pins;
    }
    return GPIO_RET_OK;
}

Gpio_Return_t GPIO_SetInterruptEvent(PortF_PinConfig_t pins, PortF_IntEventConfig_t event) {
    if(event == PORTF_INT_RISING) {
        GPIO_PORTF_IEV_R |= pins;
    } else {
        GPIO_PORTF_IEV_R &= ~pins;
    }
    return GPIO_RET_OK;
}

Gpio_Return_t GPIO_SetInterruptMask(PortF_PinConfig_t pins, PortF_IntMaskConfig_t mask) {
    if(mask == PORTF_INT_MASK_ENABLE) {
        GPIO_PORTF_IM_R |= pins;
    } else {
        GPIO_PORTF_IM_R &= ~pins;
    }
    return GPIO_RET_OK;
}

Gpio_Return_t GPIO_ClearInterrupt(PortF_PinConfig_t pins) {
    GPIO_PORTF_ICR_R = pins;
    return GPIO_RET_OK;
}

Gpio_Return_t PORTF_init(PinConfig_t PortF_PinConfigs[] ) {
	int i;
    volatile unsigned long delay;

    // Activate clock for Port F
    SYSCTL_RCGC2_R |= 0x00000020; 
    delay = SYSCTL_RCGC2_R;

    // Unlock GPIO Port F
    GPIO_PORTF_LOCK_R = 0x4C4F434B; 
    GPIO_PORTF_CR_R = (1 << 0 | 1 << 4); // Allow changes to PF0 and PF4

    // Iterate over the pin configurations

    for ( i = 0; i < 5; i++) {
        PortF_PinConfig_t pin = (PortF_PinConfig_t)(1 << i); // Map index to bit position

        GPIO_SetDigitalAnalogSelect(pin, PortF_PinConfigs[i].mode);
        GPIO_SetPinDirection(pin, PortF_PinConfigs[i].direction);
        GPIO_SetAlternateFunction(pin, PortF_PinConfigs[i].function);
        GPIO_SetPullUp(pin, PortF_PinConfigs[i].pullup);
        GPIO_SetInterruptSensitivity(pin, PortF_PinConfigs[i].intsen);
        GPIO_SetInterruptEdgeMode(pin, PortF_PinConfigs[i].edge);
        GPIO_SetInterruptEvent(pin, PortF_PinConfigs[i].event);
        GPIO_SetInterruptMask(pin, PortF_PinConfigs[i].mask);

        // Clear any existing interrupt flags
        GPIO_ClearInterrupt(pin);
    }

    return GPIO_RET_OK;
}


