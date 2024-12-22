void Delay100ms(unsigned long count);

void draw(void);
void display(void);

void Delay1a00ms(unsigned long count);
extern const unsigned char logo[];

extern const unsigned char food[] ;

extern const unsigned char space[];

extern const unsigned char ball[];

extern const unsigned char PlayerShip0[] ;

extern int ballY,ballX,playerScore,timerflag,sw1flag,sw2flag;

extern int gameGrid[21][8]; 

void EnableInterrupts(void);
void WaitForInterrupt(void);


