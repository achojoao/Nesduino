#ifndef GAMESNAKE_H
#define GAMESNAKE_H

#include "Feature.h"
#include "Achojoao_Nesduino.h"
#include "Game.h"

class GameSnake: public Game {
  
public:

  GameSnake() {}
    
  ~GameSnake() {}

  virtual void showIntro() {
    if (!introScrolled) {
      Nesduino.scrollText("Snake");                
      introScrolled = true;
    } else {
      Nesduino.clearScreen();    
      Nesduino.drawPixel(0,6,HIGH);
      Nesduino.drawLine(1,6,1,7,HIGH);
      Nesduino.drawPixel(2,5,HIGH);
      Nesduino.drawPixel(2,5,HIGH);
      Nesduino.fillRoundRect(3,0,5,5,0,HIGH);
      Nesduino.drawPixel(4,1,LOW);
      Nesduino.drawPixel(6,3,LOW);
      Nesduino.write();
    }
  }

  virtual void start() {
    newGame();    
  }

  virtual void loop() {
    if (!gameFinished) {
      long currentMillis = millis();
      if (currentMillis - lastMillis >= 250) {
        lastMillis = currentMillis;
        checkSnakeCollision();
        moveSnake();              
        if (isAppleEaten()) {
          playAppleSound();
          apple++;          
          moveApple();          
        }
        drawSnakeAndApple();        
      }
    } else {
      showIntro();
    }
  }

  virtual void finish() {
    introScrolled = false;
  }
   
  virtual void aPressed() {
    newGame();    
    playIntroMusic();
    gameFinished = false;
  }

  virtual void bPressed() {    
  }

  virtual void upPressed() {
    moveSnakeUp();    
  }

  virtual void downPressed() {
    moveSnakeDown();
  }

  virtual void leftPressed() {
    moveSnakeLeft();
  }

  virtual void rightPressed() {
    moveSnakeRight();
  }
  
private:

  int snake[64][2];
  int snakeX;
  int snakeY;
  int apple;
  int appleX;
  int appleY;
  int dir;
  long lastMillis;
  int gameFinished = true;    
  bool introScrolled = false;

  void newGame() {
    snake[64][2] = {-1};
    snake[0][0] = 3;
    snake[0][1] = 3;
    snakeX = 4;
    snakeY = 3;
    appleX = random(0,8);
    appleY = random(0,8);
    apple = 2;
    dir = 1;
    lastMillis = 0;
  }

  void playIntroMusic() {
    Nesduino.playTone(NOTE_C5, 100, true); 
    Nesduino.playTone(NOTE_E5, 100, true);
    Nesduino.playTone(NOTE_G5, 100, true);
    Nesduino.playTone(NOTE_C5, 100, true); 
    Nesduino.playTone(NOTE_E5, 100, true);
    Nesduino.playTone(NOTE_G5, 100, true);      
    Nesduino.playTone(NOTE_C5, 100, true); 
    Nesduino.playTone(NOTE_E5, 100, true);
    Nesduino.playTone(NOTE_G5, 400, true);
  }
  
  void moveSnakeUp() {
    if (dir != 2) {
      dir = 0;
    }
  }

  void moveSnakeDown() {
    if (dir != 0) {
      dir = 2;
    }
  }

  void moveSnakeLeft() {
    if (dir != 1) {
      dir = 3;
    }
  }

  void moveSnakeRight() {
    if (dir != 3) {
      dir = 1;
    }
  }

  void moveSnake() {    
    for (int i = 63; i >= 0; i--) {
      if (i < apple) {
        snake[i][0] = snake[i-1][0];
        snake[i][1] = snake[i-1][1];
      } else {
        snake[i][0] = -1;
        snake[i][1] = -1;
      }
    }
    snake[0][0] = snakeX;
    snake[0][1] = snakeY;
    if (dir == 0) {
      snakeY--;
    } else if (dir == 1) {
      snakeX++;
    } else if (dir == 2) {
      snakeY++;
    } else if (dir == 3) {
      snakeX--;
    }
  }

  void drawSnakeAndApple() {
    Nesduino.clearScreen();
    Nesduino.drawPixel(snakeX,snakeY,HIGH);
    for (int i = 0; i < apple; i++) {
      if (snake[i][0] > -1) {
        Nesduino.drawPixel(snake[i][0],snake[i][1],HIGH);
      }
    }    
    Nesduino.drawPixel(appleX,appleY,HIGH);
    Nesduino.write();
  }

  bool isAppleEaten() {
    return (snakeX == appleX && snakeY == appleY);
  }

  void playAppleSound() {
    Nesduino.playTone(NOTE_C5, 30, true);
    Nesduino.playTone(NOTE_C6, 30, true);
    Nesduino.playTone(NOTE_C7, 30, true);
  }
  
  void moveApple() {
    boolean worldMap[8][8];
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {        
          worldMap[i][j] = true; 
      }
    }
    for (int i = 0; i < 64; i++) {
      if (snake[i][0] > -1) {        
        worldMap[snake[i][0]][snake[i][1]] = false;
      }
    }
    worldMap[snakeX][snakeY] = false;
    int pixelsFree[64][2];
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        if (worldMap[i][j] == true) {
          pixelsFree[(i * 8) + j][0] = i;
          pixelsFree[(i * 8) + j][1] = j;
        } else {
          pixelsFree[(i * 8) + j][0] = -1;
          pixelsFree[(i * 8) + j][1] = -1;
        }
      }
    }           
    int pos; 
    do {
      pos = random(0, 64);  
      appleX = pixelsFree[pos][0];
      appleY = pixelsFree[pos][1];
    } while(appleX == -1);
  }
  
  void checkSnakeCollision() {
    if (snakeY < 0 || snakeY > 7 || snakeX < 0 || snakeX > 7) {
      gameLost();
    } else if (isHeadInBody()) {
      gameLost();
    }
  }

  bool isHeadInBody() {
    for (int i = 0; i < 64; i++) {
      if (snake[i][0] == snakeX && snake[i][1] == snakeY) {
        return true;
      }
    }   
    return false;
  }

  void gameLost() {
    displaySkull();    
    Nesduino.playTone(NOTE_G5, 300, true);
    Nesduino.playTone(NOTE_G5, 300, true);  
    Nesduino.playTone(NOTE_E5, 300, true); 
    Nesduino.playTone(NOTE_D5, 300, true);
    Nesduino.playTone(NOTE_C5, 600, true);    
    drawNumber(apple - 2);
    delay(5000);    
    gameFinished = true;    
  }
  
  void displaySkull() {
    Nesduino.clearScreen();    
    int xStart = random(0,2);
    Nesduino.drawLine(xStart+1,1,xStart+5,1,HIGH);
    Nesduino.drawLine(xStart,2,xStart+6,2,HIGH);
    Nesduino.drawPixel(xStart,3,HIGH);
    Nesduino.drawPixel(xStart+3,3,HIGH);
    Nesduino.drawPixel(xStart+6,3,HIGH);
    Nesduino.drawLine(xStart,4,xStart+6,4,HIGH);
    Nesduino.drawLine(xStart+1,5,xStart+5,5,HIGH);
    Nesduino.drawPixel(xStart+1,6,HIGH);
    Nesduino.drawPixel(xStart+3,6,HIGH);
    Nesduino.drawPixel(xStart+5,6,HIGH);
    Nesduino.write();
  }

};

#endif
