#ifndef GAMECATMICE_H
#define GAMECATMICE_H

#include "Feature.h"
#include "Achojoao_Nesduino.h"
#include "Game.h"

class GameCatMice: public Game {
  
public:

  GameCatMice() {}
    
  ~GameCatMice() {}

  virtual void showIntro() {
    if (!introScrolled) {
      Nesduino.scrollText("Cat&Mice");
      introScrolled = true;
    } else {
      Nesduino.clearScreen();         
      Nesduino.drawLine(2,1,4,1,HIGH); 
      Nesduino.drawLine(2,6,4,6,HIGH);
      Nesduino.drawLine(2,1,2,6,HIGH);  
      Nesduino.drawLine(4,1,4,6,HIGH);  
      Nesduino.drawLine(4,5,7,4,HIGH);  
      Nesduino.drawCircle(1,1,1,HIGH);
      Nesduino.drawCircle(5,1,1,HIGH);
      Nesduino.write();
    }    
  }

  virtual void start() {
    newGame();    
    gameFinished = true;
  }

  virtual void loop() {
    if (!gameFinished) {
      calculateCatTime();
      if (millis() - lastCatMovement > catTime) {
        moveCat();
        lastCatMovement = millis();
      }
      drawScene();
      if (isMiceHunted()) {
        gameLost();
      } else {
        moveCheese();
        if (isCheeseEaten()) {
          cheeseTime = millis();
          cheeseNeedToMoved = true;
          cheese++;
          if (cheese > 99) {
            cheese = 0;
          }
          playEatSound();          
        }
      }
    } else {
      showIntro();
    }
  }

  virtual void finish(){
    introScrolled = false;
  }
   
  virtual void aPressed() {    
    newGame();    
    playIntroMusic();
  }

  virtual void bPressed() {
  }

  virtual void upPressed() {
    moveMiceUp();
  }

  virtual void downPressed() {
    moveMiceDown();
  }

  virtual void leftPressed() {
    moveMiceLeft();
  }

  virtual void rightPressed() {
    moveMiceRight();
  }
  
private:
  int catX = 0;
  int catY = 0;
  int miceX = 0;
  int miceY = 0;
  int cheeseX = 0;
  int cheeseY = 0;
  bool gameFinished = true;
  int lastCatMovement = 0;
  int cheese = 0;
  long catTime = 0;
  long cheeseTime = 0;
  bool cheeseNeedToMoved = true;
  bool introScrolled = true;

  void newGame() {
    cheese = 0;
    catTime = 800;
    cheeseNeedToMoved = true;
    randomLocateCatAndMice();
    gameFinished = false;
  }

  void randomLocateCatAndMice() {
    int quadrant = random(0,4);
    if (quadrant == 0) {
      catX = random(0,2);
      catY = random(0,2);  
      miceX = random(4,8);
      miceY = random(4,8);  
    } else if (quadrant == 1) {
      catX = random(5,7);
      catY = random(0,2);
      miceX = random(0,4);
      miceY = random(4,8);  
    } else if (quadrant == 2) {
      catX = random(0,2);
      catY = random(5,7);
      miceX = random(4,8);
      miceY = random(0,4);  
    } else if (quadrant == 3) {
      catX = random(5,7);
      catY = random(5,7);
      miceX = random(0,4);
      miceY = random(0,4);  
    }
  }

  void playIntroMusic() {
    Nesduino.playTone(NOTE_C5, 200, true);    
    Nesduino.playTone(NOTE_C5, 200, true);
    Nesduino.playTone(NOTE_D5, 200, true);
    Nesduino.playTone(NOTE_E5, 200, true);
    Nesduino.playTone(NOTE_C5, 200, true);
    Nesduino.playTone(NOTE_E5, 200, true);
    Nesduino.playTone(NOTE_D5, 400, true);   
  }

  void moveMiceUp() {
    miceY--;
    if (miceY < 0) {
      miceY = 7;
    }
  }

  void moveMiceDown() {
    miceY++;
    if (miceY > 7) {
      miceY = 0;
    }
  }

  void moveMiceLeft() {
    miceX--;
    if (miceX < 0) {
      miceX = 7;
    }
  }

  void moveMiceRight() {
    miceX++;
    if (miceX > 7) {
      miceX = 0;
    }
  }

  void moveCat() {    
    int diffX = miceX - catX;
    int diffY = miceY - catY;
    if (diffX > 0) {
      catX++;
      if (catX > 6) {
        catX = 6;
      }
    } else if (diffX < 0) {
      catX--;
      if (catX < 0) {
        catX = 0;
      }
    }
    if (diffY > 0) {
      catY++;
      if (catY > 6) {
        catY = 6;
      }
    } else if (diffY < 0) {
      catY--;
      if (catY < 0) {
        catY = 0;
      }
    }
  }

  void calculateCatTime() {
    catTime = 800 - (50 * (cheese / 10));
  }

  void drawScene() {
    Nesduino.clearScreen();
    Nesduino.drawPixel(miceX,miceY,HIGH);    
    Nesduino.drawPixel(cheeseX,cheeseY,cheeseNeedToMoved ? (miceX == cheeseX && miceY == cheeseY) ? HIGH: LOW : HIGH);
    Nesduino.fillRoundRect(catX,catY,2,2,0,HIGH);
    Nesduino.write();
  }

  bool isMiceHunted() {
    if ((miceX == catX || miceX == catX + 1) &&
      (miceY == catY || miceY == catY + 1)) {
      return true;
    } else {
      return false;
    }
  }

  bool isCheeseEaten() {
    return (!cheeseNeedToMoved && miceX == cheeseX && miceY == cheeseY);
  }

  void playEatSound() {
    Nesduino.playTone(NOTE_C6, 50, true);    
    Nesduino.playTone(NOTE_G5, 50, true);    
  }

  void moveCheese() {
    if (cheeseNeedToMoved) {
      if (millis() - cheeseTime >= 1000) {
        int quadrant = mouseInQuadrant();
        if (quadrant == 0) {
          cheeseX = random(4,8);
          cheeseY = random(4,8);  
        } else if (quadrant == 1) {
          cheeseX = random(0,4);
          cheeseY = random(4,8);  
        } else if (quadrant == 2) {
          cheeseX = random(4,8);
          cheeseY = random(0,4);  
        } else if (quadrant == 3) {
          cheeseX = random(0,4);
          cheeseY = random(0,4);  
        }        
        cheeseNeedToMoved = false;
      }      
    }
  }

  int mouseInQuadrant() {
    if (miceX >= 0 && miceX < 4 && miceY >= 0 && miceY < 4) {
      return 0;
    } else if (miceX >= 4 && miceX < 8 && miceY >= 0 && miceY < 4) {
      return 1;
    } else if (miceX >= 0 && miceX < 4 && miceY >= 4 && miceY < 8) {
      return 2;
    } else if (miceX >= 4 && miceX < 8 && miceY >= 4 && miceY < 8) {
      return 3;
    }
  }
  
  void gameLost() {
    displaySkull();
    Nesduino.playTone(NOTE_GS3, 300, true);  
    Nesduino.playTone(NOTE_G3, 300, true);  
    Nesduino.playTone(NOTE_FS3, 300, true);  
    Nesduino.playTone(NOTE_F3, 900, true);    
    drawNumber(cheese);
    delay(5000);    
    gameFinished = true;    
  }
  
  void displaySkull() {
    Nesduino.clearScreen();    
    int xStart =random(0,2);
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
