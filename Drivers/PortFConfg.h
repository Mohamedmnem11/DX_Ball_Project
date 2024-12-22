#include "Drivers/Portf_Driver.h"
#include "../Game/tm4c123gh6pm.h"

void GPIOPortF_Handler(void);
void EnableInterrupts(void);
extern PinConfig_t PortF_PinConfigs[] ;

extern int playerX,sw1flag,sw2flag;

void Nokia5110_PrintBMP2(unsigned char xpos, unsigned char ypos, const unsigned char *ptr, unsigned char threshold, unsigned char clear);

extern const unsigned char PlayerShip0[];

