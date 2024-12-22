#include "../Game/tm4c123gh6pm.h"
extern int playerLives;
extern const unsigned char food[] ;
extern const unsigned char space[];
extern const unsigned char ball[];
extern const unsigned char PlayerShip0[];
extern void WinGame(void);
extern void EndGame(void);
extern void display(void);
int playGame(void);
extern int gameGrid[21][8];
void Delay100ms(unsigned long count);

void Nokia5110_PrintBMP2(unsigned char xpos, unsigned char ypos, const unsigned char *ptr, unsigned char threshold, unsigned char clear);
