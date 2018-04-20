#ifndef ANIMATIONFILL_H
#define ANIMATIONFILL_H

#include "Animation.h"
#include "Achojoao_Nesduino.h"

class AnimationFill: public Animation {
  
public:

  AnimationFill() {}
    
  ~AnimationFill() {}

  virtual void start() {  
    resetValues();
    calculateSpiral();
  }

  virtual void display() {    
    displayFillAnimation();    
  }

  virtual void finish() {
    resetValues();
  }
  
private:
  int spiral[64][2];
  long lastMillis;
  int fillAnimation;
  int i;
  int j;
  
  void resetValues() {
    Nesduino.clearScreen();
    Nesduino.setIntensity(3);
    lastMillis = 0;
    fillAnimation = 0;
    i = 0;
    j = 0;
  }

  void displayFillAnimation() {
    long currentMillis = millis();
    if (currentMillis - lastMillis >= 50) {
      lastMillis = currentMillis;
      if (fillAnimation == 0) {
        if (i < 8) {          
          if (j < 8) {
            Nesduino.drawPixel(i,j,HIGH);
            j++;
          }
          if (j == 8) {
            i++;
            j = 0;
          }
        } else {
          fillAnimation++;
          i = 0;
          j = 0;
        }
      } else if (fillAnimation == 1) {
        if (i < 8) {          
          if (j < 8) {
            Nesduino.drawPixel(i,j,LOW);
            j++;
          }
          if (j == 8) {
            i++;
            j = 0;
          }
        } else {
          fillAnimation++;
          i = 0;
          j = 0;
        }
      } else if (fillAnimation == 2) {
        if (i < 8) {          
          if (j < 8) {
            Nesduino.drawPixel(i,j,HIGH);
            j++;
          }
          if (j == 8) {
            i++;
            j = 0;
          }
        } else {
          fillAnimation++;
          i = 7;
          j = 7;
        }       
      } else if (fillAnimation == 3) {
        if (i >= 0) {          
          if (j >= 0) {
            Nesduino.drawPixel(i,j,LOW);
            j--;
          }
          if (j < 0) {
            i--;
            j = 7;
          }
        } else {
          fillAnimation++;
          i = 0;
          j = 0;
        }        
      } else if (fillAnimation == 4) {
        if (i < 16) {          
          Nesduino.fillTriangle(0,i,i,0,0,i,HIGH);     
          i++;          
        } else {
          fillAnimation++;
          i = 0;
          j = 0;
        }
      } else if (fillAnimation == 5) {
        if (i < 16) {          
          Nesduino.fillTriangle(0,i,i,0,0,i,LOW);
          i++;          
        } else {
          fillAnimation++;
          i = 0;
          j = 0;
        }
      } else if (fillAnimation == 6) {
        if (i < 8) {          
          Nesduino.drawLine(0,i,7,i,HIGH);
          i++;          
        } else {
          fillAnimation++;
          i = 0;
          j = 0;
        }
      } else if (fillAnimation == 7) {
        if (i < 8) {          
          Nesduino.drawLine(0,i,7,i,LOW);
          i++;          
        } else {
          fillAnimation++;
          i = 0;
          j = 0;
        }
      } else if (fillAnimation == 8) {
        if (i < 64) {          
          Nesduino.drawPixel(4+spiral[i][1],3+spiral[i][0],HIGH);
          i++;          
        } else {
          fillAnimation++;
          i = 0;
          j = 0;
        }
      } else if (fillAnimation == 9) {
        if (i < 64) {          
          Nesduino.drawPixel(4+spiral[i][1],3+spiral[i][0],LOW);
          i++;          
        } else {
          fillAnimation = 0;
          i = 0;
          j = 0;
        }
      }
      Nesduino.write();
    }
  }
  
  void calculateSpiral() {
      int x = 0;
      int y = 0;
      for (int i = 0; i < 64; i++) {
        spiral[i][0] = x;
        spiral[i][1] = y;
        if(abs(x) <= abs(y) && (x != y || x >= 0))
          x += ((y >= 0) ? 1 : -1);
        else
          y += ((x >= 0) ? -1 : 1);
      }
  }

};

#endif
