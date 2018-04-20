#ifndef ANIMATIONGOL_H
#define ANIMATIONGOL_H

#include "Animation.h"
#include "Achojoao_Nesduino.h"

class AnimationGOL: public Animation {
  
public:

  AnimationGOL() {}
    
  ~AnimationGOL() {}

  virtual void start() {  
    restartWorld();
  }

  virtual void display() {
    long currentMillis = millis();
    if (currentMillis - lastMillis >= 1000) {
      lastMillis = currentMillis;                  
      for (byte i = 0; i < 8; i++) {
        for (byte j = 0; j < 8; j++) {  
          if (i == 0 || i == 7 || j == 0 || j == 7) {
            TEMP_WORLD[i * 7 + j] = 0;
          } else {
            byte num_alive = WORLD[i - 1][j - 1] + WORLD[i - 1][j] + WORLD[i - 1][j + 1] + WORLD[i][j - 1] + WORLD[i][j + 1] + WORLD[i + 1][j - 1] + WORLD[i + 1][j] + WORLD[i + 1][j + 1];
            bool state = WORLD[i][j];  
            if (num_alive == 3) {
              TEMP_WORLD[i * 7 + j] = 1;
            } else if (num_alive == 2) {
              TEMP_WORLD[i * 7 + j] = state;
            } else {
              TEMP_WORLD[i * 7 + j] = 0;
            }
          }
        }
      }
      for (byte i = 0; i < 8; i++) {
        for (byte j = 0; j < 8; j++) {
          WORLD[i][j] = TEMP_WORLD[i * 7 + j];
        }
      }
      if (checkForRestart()) {
        restartWorld();
      } else {
        printWorld();
        gen++;      
      }
    }
  }

  virtual void finish() {
    Nesduino.clearScreen();
  }
  
private:
  
  bool TEMP_WORLD[64];
  bool AUX_WORLD[64];
  bool WORLD[8][8];
  int lastMillis;
  int gen;
  
  bool checkForRestart() {  
    if (gen > 100) {
      return true;
    }
    for (byte i = 0; i < 8; i++) {
      for (byte j = 0; j < 8; j++) {
        if (WORLD[i][j]) {
          return false;
          break;
        }
      }
    }
    for (byte i = 0; i < 8; i++) {
      for (byte j = 0; j < 8; j++) {
        AUX_WORLD[i * 7 + j] = WORLD[i][j];
      }
    }
    for (byte i = 0; i < 64; i++) {
      if (AUX_WORLD[i] != TEMP_WORLD[i]) {
        return false;
      }
    }  
    return true;
  }
  
  void restartWorld() {
    Nesduino.clearScreen();
    randomSeed(analogRead(5));
    for (byte i = 0; i < 8; i++) {
      for (byte j = 0; j < 8; j++) {
        WORLD[i][j] = random(0, 2);
      }
    }
    lastMillis = 0;
    gen = 0;
  }
  
  void printWorld() {
    for (byte j = 0; j < 8; j++) {
      for (byte i = 0; i < 8; i++) {
        if (WORLD[i][j]) {
          Nesduino.drawPixel(j, i, HIGH);
        } else {
          Nesduino.drawPixel(j, i, LOW);
        }
      }
    }
    Nesduino.write();
  }

};

#endif
