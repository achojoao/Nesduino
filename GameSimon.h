#ifndef GAMESIMON_H
#define GAMESIMON_H

#include "Feature.h"
#include "Achojoao_Nesduino.h"
#include "Game.h"

#define MAX_SEQUENCE    400
#define NO_BUTTON       -1
#define FAILURE_TONE    100
#define SEQUENCE_DELAY  800
#define GUESS_TIMEOUT   3000
#define DEBOUNCE        250

int freqs[] = {415, 252, 209, 310};

class GameSimon: public Game {
  
public:

  GameSimon() {}
    
  ~GameSimon() {}

  virtual void showIntro() {    
    if (!introScrolled) {
      Nesduino.scrollText("Simon");
      introScrolled = true;
    } else {
      Nesduino.clearScreen();         
      Nesduino.fillScreen(HIGH);
      Nesduino.drawLine(0,0,7,7,LOW);
      Nesduino.drawLine(7,0,0,7,LOW);
      Nesduino.write();
    }  
  }

  virtual void start() {
    skillLevel = 1;
    randomSeed(millis());
    gameFinished = true;
    startAnimation = true;
  }

  virtual void loop() {
    if (!gameFinished) {
      showSequence();
      for (int s=0; s<currentStep; s++) {
        if (!gameFinished) {
          startGuessTime = millis();
          guess = NO_BUTTON;
          while ((millis() - startGuessTime < GUESS_TIMEOUT) && (guess==NO_BUTTON)) {            
            guess = getButtonPress();           
            delay(1);
          }
          if (guess != simonSequence[s]) {
            gameLost(simonSequence[s]);
          }
        }        
      }
      if (!gameFinished) {
        currentStep++;
        if (currentStep > sequenceLength) {
          delay(SEQUENCE_DELAY);
          gameWon();
        }
        delay(SEQUENCE_DELAY);
      }
    } else {
      if (startAnimation) {
        indicateButton(3, 300);
        indicateButton(1, 300);
        indicateButton(2, 300);
        indicateButton(0, 300);
        startAnimation = false;
      } else {
        drawNumber(skillLevel);
      } 
    }
  }

  virtual void finish() {
    introScrolled = false;
  }
   
  virtual void aPressed() {
    gameFinished = false;
    newGame();    
    delay(1000);
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

  boolean startAnimation;
  int simonSequence[MAX_SEQUENCE];
  int skillLevel;
  int sequenceLength;
  int currentStep;
  unsigned long startGuessTime;
  int guess;
  boolean gameFinished;
  boolean introScrolled = false;

  void newGame() {
    sequenceLength = (skillLevel * 4);
    for (int i=0; i<sequenceLength; i++) {
      simonSequence[i] = random(4);
    }
    currentStep = 1;    
  }
  
  void indicateButton(int b, int duration) {    
    drawArrow(b,false);
    Nesduino.playTone(freqs[b], duration, true);
  }
  
  void showSequence() {
    int toneDuration;
    if (currentStep<=5) {
      toneDuration = 420;
    } else if (currentStep<=13) {
      toneDuration = 320;
    } else {
      toneDuration = 220;
    }
    for (int i=0; i<currentStep; i++) {
      delay(50);
      indicateButton(simonSequence[i], toneDuration);
    }
  }
  
  int getButtonPress() {
    byte keys = Nesduino.readKeys();    
    if (Nesduino.upPressed(keys)) {
      indicateButton(0, DEBOUNCE);
      return 0; 
    }  
    if (Nesduino.downPressed(keys)) {
      indicateButton(2, DEBOUNCE);
      return 2; 
    } 
    if (Nesduino.leftPressed(keys)) {
      indicateButton(3, DEBOUNCE);
      return 3;
    }
    if (Nesduino.rightPressed(keys)) {
      indicateButton(1, DEBOUNCE);
      return 1;
    }
    return NO_BUTTON;
  }
  
  void gameLost(int b) {
    drawArrow(b,true);
    Nesduino.playTone(FAILURE_TONE, 1500, true);
    gameFinished = true;
    currentStep = 0;
    skillLevel = 1;
    delay(GUESS_TIMEOUT);    
  }
  
  void gameWon() {
    for (int i=0; i<5; i++) {
      indicateButton(3, 100);
      indicateButton(1, 100);
      indicateButton(2, 100);
      indicateButton(0, 100);
    }     
    gameFinished = true;
    currentStep = 0;
    skillLevel++;
    if (skillLevel > 99) {
      skillLevel = 0;  
    }
  }

  void drawArrow(int b, bool inverted) {    
    Nesduino.fillScreen(inverted ? HIGH : LOW);
    int color = inverted ? LOW : HIGH;
    if (b == 0) {
      Nesduino.fillRoundRect(2,4,4,4,0,color);
      Nesduino.drawLine(1,3,6,3,color);
      Nesduino.drawLine(2,2,5,2,color);
      Nesduino.drawLine(3,1,4,1,color);
    } else if (b == 1) {
      Nesduino.fillRoundRect(0,2,4,4,0,color);
      Nesduino.drawLine(4,1,4,6,color);
      Nesduino.drawLine(5,2,5,5,color);
      Nesduino.drawLine(6,3,6,4,color);      
    } else if (b == 2) {
      Nesduino.fillRoundRect(2,0,4,4,0,color);
      Nesduino.drawLine(1,4,6,4,color);
      Nesduino.drawLine(2,5,5,5,color);
      Nesduino.drawLine(3,6,4,6,color);
    } else if (b == 3) {
      Nesduino.fillRoundRect(4,2,4,4,0,color);
      Nesduino.drawLine(3,1,3,6,color);
      Nesduino.drawLine(2,2,2,5,color);
      Nesduino.drawLine(1,3,1,4,color);
    }
    Nesduino.write();
  }

};

#endif
