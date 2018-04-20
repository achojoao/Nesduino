#ifndef GAMEFLAPPY_H
#define GAMEFLAPPY_H

#include "Feature.h"
#include "Achojoao_Nesduino.h"
#include "Game.h"

class GameFlappy: public Game {
  
public:

  GameFlappy() {}
    
  ~GameFlappy() {}

  virtual void showIntro() {
    if (!introScrolled) {      
      Nesduino.scrollText("Flappy Bird");                      
      introScrolled = true;
    } else {
      Nesduino.clearScreen();    
      Nesduino.drawLine(0,3,0,5,HIGH);
      Nesduino.drawLine(1,6,3,4,HIGH);
      Nesduino.drawLine(2,7,4,7,HIGH);
      Nesduino.drawLine(4,7,4,4,HIGH);
      Nesduino.drawLine(5,4,5,1,HIGH);
      Nesduino.drawLine(0,4,0,3,HIGH);
      Nesduino.drawLine(3,0,4,0,HIGH);
      Nesduino.drawLine(2,1,2,3,HIGH);
      Nesduino.drawLine(2,3,0,3,HIGH);
      Nesduino.drawPixel(4,2,HIGH);
      Nesduino.drawLine(5,6,6,6,HIGH);
      Nesduino.drawLine(7,5,6,4 ,HIGH);
      Nesduino.write();
    }
  }

  virtual void start() {
    introScrolled = true;
    showIntro();    
    playIntroMusic();
    newGame();
  }

  virtual void loop() {
    if (!gameFinished) {      
      long currentMillis = millis();
      if (currentMillis - lastMillis > 100) {
        checkCollision();
        lastMillis = currentMillis;
        letGravityDoesItJob();
        displayBirdAndWalls();
        moveWalls();
      }
    } else {
      showIntro();    
    }
  }

  virtual void finish() {
    introScrolled = false;
  }
   
  virtual void aPressed() {
    if (!gameFinished) {
      flyBird();
    } else {                    
      newGame();
      playIntroMusic();
    }
  }

  virtual void bPressed() {
  }

  virtual void upPressed() {
  }

  virtual void downPressed() {
  }

  virtual void leftPressed() {
  }

  virtual void rightPressed() {
  }
  
private:

  int birdX = 2;
  int birdY = 2;
  long lastMillis = 0;
  bool gameFinished = true;
  int walls[8][2];
  long lastWall = 0;
  int wallsSurvived = 0;
  bool introScrolled = false;

  void newGame() {    
    birdX = 2;
    birdY = 2;
    lastMillis = 0;
    lastWall = 0;
    wallsSurvived = 0;
    for (int i=0; i<8; i++) {
      for (int j=0; j<8; j++) {
        walls[i][j] = 0;
      }
    }        
    gameFinished = false;
  }

  void playIntroMusic() {
    for (int i=0; i< 2; i++) {
      Nesduino.playTone(NOTE_E5, 100, true);    
      Nesduino.playTone(NOTE_G5, 100, true);
      Nesduino.playTone(NOTE_E5, 100, true);
      Nesduino.playTone(NOTE_G5, 100, true);    
      Nesduino.playTone(NOTE_C5, 100, true);
      Nesduino.playTone(NOTE_G5, 100, true);       
    }
  }

  void checkCollision() {
    if (walls[birdX][0] > 0) {
      if (birdY < 0) {
        birdY = 0;
      }
      if (birdY < walls[birdX][1] || birdY > walls[birdX][1] + walls[birdX][0] - 1) {        
        gameLost(true);
      }
    }
  }

  void flyBird() {
    checkCollision();
    playFlySound();
    birdY = birdY - 2;    
    if (birdY < 0) {      
      birdY = -1;
    }
  }

  void playFlySound() {
    for (int i = 4000; i < 4500; i = i + 50) {
      Nesduino.playTone(i, 5, true);
    }
  }

  void letGravityDoesItJob() {
    birdY++;
    if (birdY > 7) {
      gameLost(false);
    }
  }

  void displayBirdAndWalls() {
    Nesduino.clearScreen();
    Nesduino.drawPixel(birdX,birdY,HIGH);
    for (int i = 0; i < 8; i++) {
      if (walls[i][0] > 0) {
        Nesduino.drawLine(i,0,i,7,HIGH);
        Nesduino.drawLine(i,walls[i][1],i,walls[i][1] + walls[i][0] - 1,LOW);
      }
    }
    Nesduino.write();
  }

  void moveWalls() {
    if (walls[birdX -1][0] > 0) {
      wallsSurvived++;
      if (wallsSurvived > 99) {
        wallsSurvived = 0;
      }
    }
    for (int i = 0; i < 7; i++) {
      walls[i][0] = walls[i+1][0];
      walls[i][1] = walls[i+1][1];
    }
    walls[7][0] = 0;
    walls[7][1] = 0;
    if (walls[6][0] == 0 && (random(0,10) == 5 || millis() - lastWall > 2000)) {
      int holeSize = random(2,7);
      int holeHeight = random(0,(8-holeSize));
      walls[7][0] = holeSize;
      walls[7][1] = holeHeight;
      lastWall = millis();
    }  
  }

  void gameLost(bool wallCrash) {
    gameFinished = true; 
    introScrolled = true;
    for (int j = 0; j < 3; j++) {
      for (int i = 500; i > 0; i = i -50) {    
        Nesduino.playTone(i, 10, true);  
      }
    }  
    if (wallCrash) {
      flashWall();
    }         
    drawNumber(wallsSurvived);
    delay(5000);    
  }

  void flashWall() {
    for (int i = 0; i < 3; i++) {
      Nesduino.drawLine(birdX,0,birdX,7,LOW);
      Nesduino.drawLine(birdX+1,0,birdX+1,7,LOW);
      Nesduino.write();
      delay(250);
      Nesduino.drawLine(birdX+1,0,birdX+1,7,HIGH);
      Nesduino.drawLine(birdX+1,walls[birdX][1],birdX+1,walls[birdX][1] + walls[birdX][0] - 1,LOW);
      Nesduino.write();
      delay(250);          
    }    
  }

};

#endif
