#ifndef ANIMATIONSPINNER_H
#define ANIMATIONSPINNER_H

#include "Animation.h"
#include "Achojoao_Nesduino.h"

class AnimationSpinner: public Animation {
  
public:

  AnimationSpinner() {}
    
  ~AnimationSpinner() {}

  virtual void start() {  
    resetValues();
  }
  
  virtual void display() {
    long currentMillis = millis();
    if (currentMillis - lastMillis >= 50) {      
      lastMillis = currentMillis;
      Nesduino.fillScreen(LOW);      
      if (x < 7) {        
        Nesduino.drawLine(x,0,7-x,7,HIGH);        
        x++;
      } else {
        if (y < 7) {        
          Nesduino.drawLine(7,y,0,7-y,HIGH);
          y++;
          if (y == 6) {
            x = 0;
            y = 0;            
          }
        }        
      }
      Nesduino.write();
    }    
  }

  virtual void finish() {
    Nesduino.clearScreen();
    Nesduino.setIntensity(3);
    resetValues();
  }
  
private:

  long lastMillis;
  int x;
  int y;
    
  void resetValues() {
    lastMillis = 0;
    x = 0;
    y = 0;
  }
  
};

#endif
