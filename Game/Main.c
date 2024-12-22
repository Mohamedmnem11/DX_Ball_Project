#include <string.h>
#include <stdlib.h>
#include <stdint.h>




#include "tm4c123gh6pm.h"
#include "Nokia5110.h"
#include "TExaS.h"
#include "Drivers/Timer2_cfg.h"
#include "Drivers/screen_draw.h"
#include "Game/GameLogic.h"
#include "Drivers/ADC.h"
#include "Drivers/UART_INTERRUPT.h"
#include "Drivers/PortFConfg.h"




uint8_t shipX = 36;
const uint8_t shipWidth = 20;
const uint8_t screenMaxX = 84;
const uint8_t screenMinX = 0;


	
int playerLives=3;
int sw1flag=1,oldplayerX=32,sw2flag=1;
int gameGrid[21][8]; 








void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void Delay100ms(unsigned long count); // time delay in 0.1 seconds






int main(void){
	
  TExaS_Init(SSI0_Real_Nokia5110_Scope);  // set system clock to 80 MHz
	Nokia5110_Init();
	GPIO_PortF_Init();
	ADC_Init();
	UART_Init();
	EnableInterrupts();
	Timer2_Init();

	display();
  while(1){
		playGame();
		if(sw1flag && !sw2flag ) {UpdateShipPosition();}
		switch(playerLives){
			case 1:
				GPIO_PORTF_DATA_R = (1<<1);
				break;
			case 2:
				GPIO_PORTF_DATA_R = (1<<1) | (1<<2);
				break;
			case 3:
				GPIO_PORTF_DATA_R = (1<<1) | (1<<2)| (1<<3);
				break;
			case 0:
			default:
				GPIO_PORTF_DATA_R = 0x0;
				break;
		}
		
		if(playGame()==0){
		return 0;
		}
			
}

}

