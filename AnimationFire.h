#ifndef ANIMATIONFIRE_H
#define ANIMATIONFIRE_H

#include "Animation.h"
#include "Achojoao_Nesduino.h"

class AnimationFire: public Animation {
  
public:

  AnimationFire() {}
    
  ~AnimationFire() {}

  virtual void start() {  
  }

  virtual void display() {
    Nesduino.clearScreen();
    for (int i = 0; i < 8; i++) {
      Nesduino.drawLine(i,7,i,random(8),HIGH);
    }
    Nesduino.setIntensity(random(5));
    Nesduino.write();
    delay(100);
  }

  virtual void finish() {
  }
  
private:

};

#endif
