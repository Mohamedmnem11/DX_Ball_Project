#include "Game/tm4c123gh6pm.h"
#include "Drivers/PortFConfg.h"
#include "../Game/Nokia5110.h"

// Array to store configuration for each pin
 PinConfig_t PortF_PinConfigs[] = {
    // Configuration for PF0 (SW2)
    {
        DIGITAL,             /* mode */
        PORTF_DIR_INPUT,    /* direction */
        PORTF_FUNC_GPIO,    /* function */
        PORTF_PULLUP_ENABLE,/* pullup */
        PORTF_INT_EDGE,     /* intsen */
        PORTF_INT_SINGLE_EDGE, /* edge */
        PORTF_INT_FALLING,  /* event */
        PORTF_INT_MASK_ENABLE  /* mask */
    },
    // Configuration for PF1 (RED LED)
    {
        DIGITAL,             /* mode */
        PORTF_DIR_OUTPUT,    /* direction */
        PORTF_FUNC_GPIO,     /* function */
        PORTF_PULLUP_DISABLE,/* pullup */
        PORTF_INT_EDGE,      /* intsen */
        PORTF_INT_SINGLE_EDGE,/* edge */
        PORTF_INT_FALLING,   /* event */
        PORTF_INT_MASK_DISABLE /* mask */
    },
    // Configuration for PF2 (BLUE LED)
    {
        DIGITAL,             /* mode */
        PORTF_DIR_OUTPUT,    /* direction */
        PORTF_FUNC_GPIO,     /* function */
        PORTF_PULLUP_DISABLE,/* pullup */
        PORTF_INT_EDGE,      /* intsen */
        PORTF_INT_SINGLE_EDGE,/* edge */
        PORTF_INT_FALLING,   /* event */
        PORTF_INT_MASK_DISABLE /* mask */
    },
    // Configuration for PF3 (GREEN LED)
    {
        DIGITAL,             /* mode */
        PORTF_DIR_OUTPUT,    /* direction */
        PORTF_FUNC_GPIO,     /* function */
        PORTF_PULLUP_DISABLE,/* pullup */
        PORTF_INT_EDGE,      /* intsen */
        PORTF_INT_SINGLE_EDGE,/* edge */
        PORTF_INT_FALLING,   /* event */
        PORTF_INT_MASK_DISABLE /* mask */
    },
    // Configuration for PF4 (SW1)
    {
        DIGITAL,             /* mode */
        PORTF_DIR_INPUT,     /* direction */
        PORTF_FUNC_GPIO,     /* function */
        PORTF_PULLUP_ENABLE, /* pullup */
        PORTF_INT_EDGE,      /* intsen */
        PORTF_INT_SINGLE_EDGE,/* edge */
        PORTF_INT_FALLING,   /* event */
        PORTF_INT_MASK_ENABLE  /* mask */
    }
};
 
void GPIO_PortF_Init(void){
	PORTF_init(PortF_PinConfigs);
	  GPIO_PORTF_ICR_R = (1<<1)|(1<<4);          // (e) clear flags 4
		NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00400000; // (g) priority 2
  NVIC_EN0_R = 0x40000000;      // (h) enable interrupt 30 in NVIC
	
	

}



void GPIOPortF_Handler(void){ // called on touch of either SW1 or SW2
  if(GPIO_PORTF_RIS_R&0x10){  // SW1 touch
		GPIO_PORTF_ICR_R = 0x10;  // acknowledge flag0
			//GPIO_PORTF_DATA_R &= 0x00;
			//GPIO_PORTF_DATA_R |= 0x08;
   
		if(playerX <63&&!sw1flag && sw2flag){
			Nokia5110_PrintBMP2(playerX, 47,PlayerShip0, 0, 1);
	
			playerX+=4;
		}
		 if(sw2flag==1){sw1flag = 0;}  //flag to start the game
		
		
  }
  if(GPIO_PORTF_RIS_R&0x01){  // SW2 touch
		//	GPIO_PORTF_DATA_R &= 0x00;
		//GPIO_PORTF_DATA_R = 0x02;
		if(sw1flag == 1){sw2flag=0;}
    
		
		if(playerX > 0 && !sw1flag && sw2flag){
		Nokia5110_PrintBMP2(playerX, 47,PlayerShip0, 0, 1);
			playerX-=4;
		}
		GPIO_PORTF_ICR_R = 0x01;  // acknowledge flag4
	}
	Nokia5110_PrintBMP(playerX, 47, PlayerShip0, 0);
		
}



