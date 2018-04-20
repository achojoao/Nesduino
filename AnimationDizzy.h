#ifndef ANIMATIONDIZZY_H
#define ANIMATIONDIZZY_H

#include "Animation.h"
#include "Achojoao_Nesduino.h"

class AnimationDizzy: public Animation {
  
public:

  AnimationDizzy() {}
    
  ~AnimationDizzy() {}

  virtual void start() {  
    resetValues();
  }

  virtual void display() {
    long currentMillis = millis();
    if (currentMillis - lastMillis >= 500) {
      lastMillis = currentMillis;
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {        
          Nesduino.drawPixel(i,j,random(2));     
        }
      }
      Nesduino.write();
    }
  }

  virtual void finish() {
    resetValues();
  }
  
private:

  long lastMillis;

  void resetValues() {
    Nesduino.clearScreen();
    Nesduino.setIntensity(3);
    lastMillis = 0;
  }

};

#endif
