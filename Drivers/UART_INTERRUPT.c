// UART.c
// Runs on TM4C123 or LM4F120
// Lab 11 involves switching this from UART1 to UART0.
//                 switching from PC5,PC4 to PA1,PA0
// Daniel Valvano
// December 29, 2014

/* This example accompanies the book
   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2014

 Copyright 2015 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// this connection occurs in the USB debugging cable
// U0Rx (PA0) connected to serial port on PC
// U0Tx (PA1) connected to serial port on PC
// Ground connected ground in the USB cable

#include "Game/tm4c123gh6pm.h"
#include "UART_INTERRUPT.h"

#include "../Game/Nokia5110.h"
#include "Drivers/PortFConfg.h"

void Nokia5110_PrintBMP2(unsigned char xpos, unsigned char ypos, const unsigned char *ptr, unsigned char threshold, unsigned char clear);
unsigned char input;

//------------UART_Init------------
// Initialize the UART for 115200 baud rate (assuming 80 MHz UART clock),
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
// Output: none
void UART_Init(void){
	SYSCTL_RCGC1_R |= (1 << 0); // activate UART0
  SYSCTL_RCGC2_R |= (1 << 0); // activate port A
  UART0_CTL_R &= ~(1 << 0);      // disable UART
  UART0_IBRD_R = 520;                    // IBRD = int(80,000,000 / (16 * 9600)) = int(520)
  UART0_FBRD_R = 53;                     // FBRD = int(0.166667 * 64 + 0.5) = 11
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART0_LCRH_R = (3<<5);
  UART0_CTL_R |= (1 << 0) | (1 << 8) | (1 << 9);	// enable UART, RX, TX
	UART0_IFLS_R = (0 << 0);                  // set the fifo level select to 1/8
  GPIO_PORTA_AFSEL_R |= 0x03;           // enable alt funct on PA1-0
  GPIO_PORTA_DEN_R |= (1<<0) |(1<<1);             // enable digital I/O on PA1-0
                                        // configure PA1-0 as UART
  GPIO_PORTA_PCTL_R |= (1<<0)|(1<<4);
  GPIO_PORTA_AMSEL_R &= ~0x03;          // disable analog functionality on PA
	
	UART0_IM_R |= (1 << 4);
	NVIC_EN0_R |= (1 << 5);
}

char UART0_Read(void) {
    while ((UART0_FR_R & 0x10) != 0);  // Wait until RXFE is 0 (not empty)
    return (char)(UART0_DR_R & 0xFF);
}

void UART0_Handler(void){
	if(UART0_RIS_R & (1 << 4)){
		UART0_ICR_R |= (1 << 4);
		input = UART0_Read();
		UART_OutChar(input);
		switch(input){
			case('g'):
				if(playerX <63&&!sw1flag && sw2flag){
				Nokia5110_PrintBMP2(playerX, 47,PlayerShip0, 0, 1);
				playerX+=4;
				
				}
				break;
			case('f'):
				if(playerX > 0 && !sw1flag && sw2flag){
					Nokia5110_PrintBMP2(playerX, 47,PlayerShip0, 0, 1);
					playerX-=4;
					}
				break;
		}
		Nokia5110_PrintBMP(playerX, 47, PlayerShip0, 0);
		
		
	}
}
void UART0_Write(char c) {
    while ((UART0_FR_R & 0x20) != 0);  // Wait until TXFF is 0 (not full)
    UART0_DR_R = c;
}

void UART0_WriteString(const char *str) {
    while (*str) {
        UART0_Write(*str++);
    }
}


//------------UART_InChar------------
// Wait for new serial port input
// Input: none
// Output: ASCII code for key typed
unsigned char UART_InChar(void){
// as part of Lab 11, modify this program to use UART0 instead of UART1
  while((UART0_FR_R&UART_FR_RXFE) != 0);
  return((unsigned char)(UART0_DR_R&0xFF));
}

//------------UART_InCharNonBlocking------------
// Get oldest serial port input and return immediately
// if there is no data.
// Input: none
// Output: ASCII code for key typed or 0 if no character
unsigned char UART_InCharNonBlocking(void){
// as part of Lab 11, modify this program to use UART0 instead of UART1
  if((UART0_FR_R&UART_FR_RXFE) == 0){
    return((unsigned char)(UART0_DR_R&0xFF));
  } else{
    return 0;
  }
}

//------------UART_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART_OutChar(unsigned char data){
// as part of Lab 11, modify this program to use UART0 instead of UART1
  while((UART0_FR_R&UART_FR_TXFF) != 0);
  UART0_DR_R = data;
}

//------------UART_InUDec------------
// InUDec accepts ASCII input in unsigned decimal format
//     and converts to a 32-bit unsigned number
//     valid range is 0 to 4294967295 (2^32-1)
// Input: none
// Output: 32-bit unsigned number
// If you enter a number above 4294967295, it will return an incorrect value
// Backspace will remove last digit typed
unsigned long UART_InUDec(void){
unsigned long number=0, length=0;
char character;
  character = UART_InChar();
  while(character != CR){ // accepts until <enter> is typed
// The next line checks that the input is a digit, 0-9.
// If the character is not 0-9, it is ignored and not echoed
    if((character>='0') && (character<='9')) {
      number = 10*number+(character-'0');   // this line overflows if above 4294967295
      length++;
      UART_OutChar(character);
    }
// If the input is a backspace, then the return number is
// changed and a backspace is outputted to the screen
    else if((character==BS) && length){
      number /= 10;
      length--;
      UART_OutChar(character);
    }
    character = UART_InChar();
  }
  return number;
}
//------------UART_OutString------------
// Output String (NULL termination)
// Input: pointer to a NULL-terminated string to be transferred
// Output: none
void UART_OutString(unsigned char buffer[]){
// as part of Lab 11 implement this function
	while(*buffer){
    UART_OutChar(*buffer);
    buffer++;
  }
}

unsigned char String[10];
//-----------------------UART_ConvertUDec-----------------------
// Converts a 32-bit number in unsigned decimal format
// Input: 32-bit number to be transferred
// Output: store the conversion in global variable String[10]
// Fixed format 4 digits, one space after, null termination
// Examples
//    4 to "   4 "  
//   31 to "  31 " 
//  102 to " 102 " 
// 2210 to "2210 "
//10000 to "**** "  any value larger than 9999 converted to "**** "
void UART_ConvertUDec(unsigned long n) {
	// as part of Lab 11 implement this function
}


//-----------------------UART_OutUDec-----------------------
// Output a 32-bit number in unsigned decimal format
// Input: 32-bit number to be transferred
// Output: none
// Fixed format 4 digits, one space after, null termination
void UART_OutUDec(unsigned long n){
  UART_ConvertUDec(n);     // convert using your function
  UART_OutString(String);  // output using your function
}

//-----------------------UART_ConvertDistance-----------------------
// Converts a 32-bit distance into an ASCII string
// Input: 32-bit number to be converted (resolution 0.001cm)
// Output: store the conversion in global variable String[10]
// Fixed format 1 digit, point, 3 digits, space, units, null termination
// Examples
//    4 to "0.004 cm"  
//   31 to "0.031 cm" 
//  102 to "0.102 cm" 
// 2210 to "2.210 cm"
//10000 to "*.*** cm"  any value larger than 9999 converted to "*.*** cm"
void UART_ConvertDistance(unsigned long n) {
	// as part of Lab 11 implement this function
}


//-----------------------UART_OutDistance-----------------------
// Output a 32-bit number in unsigned decimal fixed-point format
// Input: 32-bit number to be transferred (resolution 0.001cm)
// Output: none
// Fixed format 1 digit, point, 3 digits, space, units, null termination
void UART_OutDistance(unsigned long n){
  UART_ConvertDistance(n);      // convert using your function
  UART_OutString(String);       // output using your function
}
