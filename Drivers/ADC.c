#include "Drivers/ADC.h"
#include <stdint.h>
#include "Game/Nokia5110.h"
#include "Drivers/PortFConfg.h"



volatile int delay = 0;
void Nokia5110_PrintBMP2(unsigned char xpos, unsigned char ypos, const unsigned char *ptr, unsigned char threshold, unsigned char clear);
// ADC initialization using bitwise operations
void ADC_Init(void) {
    SYSCTL_RCGCADC_R |= (1 << 0);             // Enable ADC0 clock
    SYSCTL_RCGCGPIO_R |= (1 << 4);            // Enable clock for Port E

    
    delay += 4;                               // Stabilization delay

    GPIO_PORTE_AFSEL_R |= (1 << 3);           // Enable alternate function on PE3
    GPIO_PORTE_DEN_R &= ~(1 << 3);            // Disable digital function on PE3
    GPIO_PORTE_AMSEL_R |= (1 << 3);           // Enable analog functionality on PE3

    ADC0_ACTSS_R &= ~(1 << 3);                // Disable Sample Sequencer 3
    ADC0_EMUX_R &= ~(0xF << 12);              // Configure as software trigger
    ADC0_SSMUX3_R = 0;                        // Set input channel to AIN0 (PE3)
    ADC0_SSCTL3_R = (1 << 1) | (1 << 2);      // Single-ended, end-of-sequence
    ADC0_ACTSS_R |= (1 << 3);                 // Enable Sample Sequencer 3
}

// Read ADC value using bitwise operations
uint16_t ADC_Read(void) {
    uint16_t result;
    ADC0_PSSI_R |= (1 << 3);                  // Initiate SS3
    while ((ADC0_RIS_R & (1 << 3)) == 0);     // Wait for conversion to complete
    result = ADC0_SSFIFO3_R & 0xFFF;          // Read 12-bit result
    ADC0_ISC_R |= (1 << 3);                   // Clear interrupt flag
    return result;
}

// Update ship position based on ADC input
void UpdateShipPosition(void) {
		
    uint16_t adcValue = ADC_Read();
		oldplayerX = playerX;
    playerX = (adcValue * (screenMaxX - shipWidth)) >> 12;  // Divide by 4096 using bit shift
	  
        DrawShip();          
}

// Draw the ship
void DrawShip(void) {
		Nokia5110_PrintBMP2(oldplayerX, 47,PlayerShip0, 0, 1);
    Nokia5110_PrintBMP2(playerX, 47, PlayerShip0, 0,0);  // 47 is the bottom of the screen
    Nokia5110_DisplayBuffer();
}



