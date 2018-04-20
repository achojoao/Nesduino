#ifndef GAMEDICE_H
#define GAMEDICE_H

#include "Feature.h"
#include "Achojoao_Nesduino.h"
#include "Game.h"

class GameDice: public Game {
  
public:

  GameDice() {}
    
  ~GameDice() {}

  virtual void showIntro() {    
    if (!introScrolled) {
      Nesduino.scrollText("Dice");
      introScrolled = true;
    } else {
      displayNumber(5);
    } 
  }

  virtual void start() {
  }

  virtual void loop() {
  }

  virtual void finish(){
    introScrolled = false;  
  }
   
  virtual void aPressed() {
    rollDice();
  }

  virtual void bPressed() {
    rollDice();
  }

  virtual void upPressed() {
    rollDice();
  }

  virtual void downPressed() {
    rollDice();
  }

  virtual void leftPressed() {
    rollDice();
  }

  virtual void rightPressed() {
    rollDice();
  }
  
private:

  boolean introScrolled = false;

  void rollDice() {
    bool rolling = true;
    long startRolling = millis();
    while (rolling) {
      int rollNumber = random(1,7);
      Nesduino.playTone(random(400,2000), 20, true);  
      displayNumber(rollNumber);
      delay(20);
      if (millis() - startRolling >= 1000) {
        rolling = false;
      }
    }
  }

  void displayNumber(int number) {
    Nesduino.clearScreen();
    if (number == 1) {
      Nesduino.fillRoundRect(3,3,2,2,0,HIGH);
    } else if (number == 2) {
      Nesduino.fillRoundRect(0,0,2,2,0,HIGH);
      Nesduino.fillRoundRect(6,6,2,2,0,HIGH);
    } else if (number == 3) {
      Nesduino.fillRoundRect(0,0,2,2,0,HIGH);
      Nesduino.fillRoundRect(6,6,2,2,0,HIGH);
      Nesduino.fillRoundRect(3,3,2,2,0,HIGH);
    } else if (number == 4) {
      Nesduino.fillRoundRect(0,0,2,2,0,HIGH);
      Nesduino.fillRoundRect(6,6,2,2,0,HIGH);
      Nesduino.fillRoundRect(0,6,2,2,0,HIGH);
      Nesduino.fillRoundRect(6,0,2,2,0,HIGH);
    } else if (number == 5) {
      Nesduino.fillRoundRect(0,0,2,2,0,HIGH);
      Nesduino.fillRoundRect(6,6,2,2,0,HIGH);
      Nesduino.fillRoundRect(0,6,2,2,0,HIGH);
      Nesduino.fillRoundRect(6,0,2,2,0,HIGH);
      Nesduino.fillRoundRect(3,3,2,2,0,HIGH);
    } else if (number == 6) {
      Nesduino.fillRoundRect(0,0,2,2,0,HIGH);
      Nesduino.fillRoundRect(6,6,2,2,0,HIGH);
      Nesduino.fillRoundRect(0,6,2,2,0,HIGH);
      Nesduino.fillRoundRect(6,0,2,2,0,HIGH);
      Nesduino.fillRoundRect(0,3,2,2,0,HIGH);
      Nesduino.fillRoundRect(6,3,2,2,0,HIGH);
    }
    Nesduino.write();
  }

};

#endif
