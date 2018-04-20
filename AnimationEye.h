#ifndef ANIMATIONEYE_H
#define ANIMATIONEYE_H

#include "Animation.h"
#include "Achojoao_Nesduino.h"

class AnimationEye: public Animation {
  
public:

  AnimationEye() {}
    
  ~AnimationEye() {}

  virtual void start() {  
    resetValues();
  }
  
  virtual void display() {
    long currentMillis = millis();
    if (currentMillis - lastMillis >= animationMillis) {      
      lastMillis = currentMillis;
      if (action >= 1 && action <= 9) {
        action = random(11);
        int randDelay = 1000 * ( 1 + random(10));
        Nesduino.clearScreen();
        Nesduino.fillRoundRect(1,1,6,6,1,HIGH);
        Nesduino.fillRoundRect(4-(action%3),2+(action/4),2,2,0,LOW);
        Nesduino.write();
        animationMillis = randDelay;
      } else {
        animationMillis = 50;
        if (j < 2) {
          if (i < 10) {
            Nesduino.clearScreen();
            Nesduino.fillRoundRect(1,1,6,6,1,HIGH);
            Nesduino.fillRoundRect(3,3,2,2,0,LOW);
            i++;            
          } else if (i < 16) {       
            Nesduino.drawLine(0,i-10,7,i-10,LOW);
            if (i == 15) {
              i = 0;
              j++;
            } else {
              i++;
            }
          }
        } else {
          j = 0;          
          action = random(11);
        }
        Nesduino.write();
      }
    }    
  }

  virtual void finish() {
    resetValues();
  }
  
private:
  
  long lastMillis;
  long animationMillis;
  int action;
  int i;
  int j;
  
  void resetValues() {
    Nesduino.clearScreen();
    Nesduino.setIntensity(3);
    lastMillis = 0;
    animationMillis = 0;
    action = 0;
    i = 0;
    j = 0;   
  }
};

#endif
