#include <stdint.h>

extern const uint8_t screenMaxX,shipWidth;
extern int oldplayerX;

void ADC_Init(void);
uint16_t ADC_Read(void);
void UpdateShipPosition(void);
void DrawShip(void);
void Delay100ms(unsigned long count);
