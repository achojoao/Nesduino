#ifndef ANIMATIONMATRIX_H
#define ANIMATIONMATRIX_H

#include "Animation.h"
#include "Achojoao_Nesduino.h"

class AnimationMatrix: public Animation {
  
public:

  AnimationMatrix() {}
    
  ~AnimationMatrix() {}

  virtual void start() {  
    resetValues();
  }

  virtual void display() {
    long currentMillis = millis();
    if (currentMillis - lastMillis >= 50) {      
      lastMillis = currentMillis;      
      for (int i = 0; i < 8 ; i++) {
        if (canDrawLine[i][0] + canDrawLine[i][1] <= 0) {
          int colorLength = random(8);
          int emptyLength = random(16);
          canDrawLine[i][0] = colorLength;
          canDrawLine[i][1] = emptyLength;
          firstLine[i] = HIGH;
        } else if (canDrawLine[i][0] > 0) {
          firstLine[i] = HIGH;
          canDrawLine[i][0]--;
        } else {
          firstLine[i] = LOW;
          canDrawLine[i][1]--;
        }
      }  
      for (int i = 7; i >= 0 ; i--) {
        for (int j = 0; j < 8 ; j++) {
          if (i == 0) {
             animatrix[i][j] = firstLine[j];
          } else {
            animatrix[i][j] = animatrix[i-1][j];
          }
        }
      }
      for (int i = 0; i < 8 ; i++) {
        for (int j = 0; j < 8 ; j++) {
          Nesduino.drawPixel(j,i,animatrix[i][j]);
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
  int canDrawLine[8][2];
  int firstLine[8];
  int animatrix[8][8];

  void resetValues() {
    Nesduino.clearScreen();
    Nesduino.setIntensity(3);
    lastMillis = 0;
    canDrawLine[8][2] = {0};
    firstLine[8] = {0};
    animatrix[8][8] = {0};
  }

};

#endif
