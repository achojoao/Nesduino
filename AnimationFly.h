#ifndef ANIMATIONFLY_H
#define ANIMATIONFLY_H

#include "Animation.h"
#include "Achojoao_Nesduino.h"

class AnimationFly: public Animation {
  
public:

  AnimationFly() {}
    
  ~AnimationFly() {}

  virtual void start() {  
    resetValues();
  }

  virtual void display() {    
    Nesduino.drawPixel(x,y,HIGH);
    Nesduino.write();
    Nesduino.drawPixel(x,y,LOW);  
    do {
      switch ( random(4) ) {
        case 0: xNext = constrain(x + 1, 0, 7); yNext = y; break;
        case 1: xNext = constrain(x - 1, 0, 7); yNext = y; break;
        case 2: yNext = constrain(y + 1, 0, 7); xNext = x; break;
        case 3: yNext = constrain(y - 1, 0, 7); xNext = x; break;
      }
    }
    while ( x == xNext && y == yNext );  
    x = xNext;
    y = yNext;
  }

  virtual void finish() {
    resetValues();
  }
  
private:

  int x = 4;
  int y = 4;
  int xNext, yNext;

  void resetValues() {
    Nesduino.clearScreen();
    Nesduino.setIntensity(3);
    x = 4;
    y = 4;
    xNext = 0;
    yNext = 0;
  }
  
};

#endif
