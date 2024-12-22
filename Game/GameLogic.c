#include "GameLogic.h"
#include "../Game/Nokia5110.h"
int playerScore,foodEaten;
int playerX =32, ballX=36 , ballY=36 , ballSpeedX =4, ballSpeedY=-4 ;



void handleBallShipCollision(){
    if(ballY >= 38 && ballX >= playerX && ballX < playerX + 20){ // Ship collision detection
        int collisionPoint = ballX - playerX;
        
        if(collisionPoint < 8){          // Left side collision
            ballSpeedX = -4;
        } else if(collisionPoint < 12 ){ // Center collision
            ballSpeedX = 0;
        } else {                         // Right side collision
            ballSpeedX = 4;
        }
        ballSpeedY = -4;                 // Ball always moves up after collision
    }
    Nokia5110_PrintBMP2(ballX, ballY, ball, 0,1);
}

void handleBallGridCollision(){
    int gridX = (ballX + ballSpeedX)/4;
    int gridY = (ballY + ballSpeedY)/4;
    
    // Special Cases
    if(ballY <= 4 && ballX >= 80){    // Top right corner case
        gridY = 2;
    }
    
    if(gridX == 21){                  // Right border in food area
        gridX = gridX-2;
        if(gameGrid[gridX][gridY] && ballSpeedY < 0){     // Moving up-right
            ballSpeedX = -4;
            ballSpeedY = -4;
        } else if(gameGrid[gridX][gridY] && ballSpeedY > 0){ // Moving down-right
            ballSpeedX = -4;
            ballSpeedY = 4;
        }
    }
    
    if((ballY <= 4 && ballX <= 0)){   // Top left corner case
        gridY = 2;
        if(gridX <= 0){
            gridX = 1;
            if(gameGrid[gridX][gridY] && ballSpeedY < 0){     // Moving up-left
                ballSpeedX = 4;
                ballSpeedY = -4;
            } else if(gameGrid[gridX][gridY] && ballSpeedY > 0){ // Moving up-right
                ballSpeedX = 4;
                ballSpeedY = 4;
            }
        }
    }
    
    if(ballY <= 4){                   // Top border collision
        gridY = 2;
        ballSpeedY = 4;
    }

    // Food collision detection and handling
    if(gridX >= 0 && gridY >= 0 && gridX < 21 && gridY < 6 && gameGrid[gridX][gridY]){
        ballX += ballSpeedX;
        ballY += ballSpeedY;
        
        // Handle different ball movement directions and food collisions
        if(ballSpeedX > 0 && ballSpeedY < 0){             // Moving up-right
            if(gameGrid[gridX][gridY + 1] && gameGrid[gridX - 1][gridY]){
                if(ballX >= 79){
                    ballSpeedY = -ballSpeedY;
                } else {
                    ballSpeedX = -ballSpeedX;
                    ballSpeedY = -ballSpeedY;
                }
            } else if(gameGrid[gridX - 1][gridY]){
                ballSpeedY = -ballSpeedY;
            } else {
                ballSpeedX = -ballSpeedX;
            }
        } else if(ballSpeedX < 0 && ballSpeedY < 0){      // Moving up-left
            if(gameGrid[gridX + 1][gridY] && gameGrid[gridX][gridY + 1]){// there is  food down and right of target food
                    if(ballX<=0){
                    ballSpeedX = -ballSpeedY;//the ball will move down
                    }else{
                    ballSpeedX = -ballSpeedX;//the ball will move right
                    ballSpeedY = -ballSpeedY;//the ball will move down
                    }
                }else if(gameGrid[gridX + 1][gridY]){// there is food right of target food
                    ballSpeedY = -ballSpeedY;//the ball will move down left
                }else{// there is no food down or right of target food
                    ballSpeedX = -ballSpeedX;//the ball will move up right
                }
            }else if(ballSpeedX < 0 && ballSpeedY > 0){//the ball is moving left down
				if(gameGrid[gridX + 1][gridY] && gameGrid[gridX][gridY - 1]){// there is  food above and right of target food
					if(ballX<=0){
						ballSpeedY = -ballSpeedY;//the ball will move up
					}else{
					ballSpeedX = -ballSpeedX;//the ball will move right
					ballSpeedY = -ballSpeedY;//the ball will move up
					}}else if(gameGrid[gridX + 1][gridY]){// there is food right of target food
					ballSpeedY = -ballSpeedY;//the ball will move up left
				}else{// there is no food above or right of target food
					ballSpeedX = -ballSpeedX;//the ball will move down right
				}
			}else if(ballSpeedX>0&&ballSpeedY>0){//the ball is moving down right
				if(gameGrid[gridX - 1][gridY] && gameGrid[gridX][gridY - 1]){// there is  food above and left of target food
					if(ballX>=79){
					ballSpeedY = -ballSpeedY;//the ball will move up
					}else{
					ballSpeedX = -ballSpeedX;//the ball will move left
					ballSpeedY = -ballSpeedY;//the ball will move up
				}}else if(gameGrid[gridX - 1][gridY]){// there is food left of target food
					ballSpeedY = -ballSpeedY;//the ball will move up right
				}else{// there is no food above or left of target food
					ballSpeedX = -ballSpeedX;//the ball will move down left
				}
			}else{//the ball is moving up
			ballSpeedY=-ballSpeedY;
			}
        
        
        gameGrid[gridX][gridY] = 0;
        playerScore += 10 ;
        ++foodEaten;
        
    } else {
        // Screen boundary checks
        if(ballX <= 0 || ballX >= 79){
            ballSpeedX = -ballSpeedX;
        }
        if(ballY < 4){
            ballSpeedY = -ballSpeedY;
        }
        if(ballY >= 47){              // Ball missed by player
            --playerLives;
            ballX = 36;
            ballY = 36;
            ballSpeedX = 4;
            ballSpeedY = -4;
        }
        ballX += ballSpeedX;
        ballY += ballSpeedY;
    }
}

int checkGameOver(){
    if(playerLives == 0){
        GPIO_PORTF_DATA_R = 0x0;
        EndGame();
        return 1;
    }
    return 0;
}

int playGame(void){
    handleBallShipCollision();
    handleBallGridCollision();
    
    if(checkGameOver()){
        return 0;
    }
    
    if(foodEaten == 84){
       
            WinGame();
            return 0;
        
    }
    
    Delay100ms(5);   // Adjust ball speed based on level
    Nokia5110_PrintBMP(ballX, ballY, ball, 0);
    Nokia5110_DisplayBuffer();
    return 1;
}

