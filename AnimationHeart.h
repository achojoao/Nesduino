#ifndef ANIMATIONHEART_H
#define ANIMATIONHEART_H

#include "Animation.h"
#include "Achojoao_Nesduino.h"

class AnimationHeart: public Animation {
  
public:

  AnimationHeart() {}
    
  ~AnimationHeart() {}

  virtual void start() {  
    resetValues();
  }

  virtual void display() {    
    long currentMillis = millis();
    if (currentMillis - lastMillis >= 100) {
      Nesduino.clearScreen();
      lastMillis = currentMillis;
      if (i == 0 || i == 2) {
        drawHeart();   
        i++;     
      } else if (i == 8) {
        i = 0;
      } else {
        i++;
      }
      Nesduino.write();
    }
  }

  virtual void finish() {
    resetValues();
  }
  
private:

  long lastMillis;
  int i;

  void resetValues() {
    Nesduino.clearScreen();
    Nesduino.setIntensity(3);
    lastMillis = 0;
    i = 0;
  }

  void drawHeart() {
    Nesduino.drawLine(1,0,2,0,HIGH);
    Nesduino.drawLine(5,0,6,0,HIGH);
    Nesduino.drawLine(0,1,7,1,HIGH);
    Nesduino.drawLine(0,2,7,2,HIGH);
    Nesduino.drawLine(0,3,7,3,HIGH);
    Nesduino.drawLine(1,4,6,4,HIGH);
    Nesduino.drawLine(2,5,5,5,HIGH);
    Nesduino.drawLine(3,6,4,6,HIGH);          
  }

};

#endif
