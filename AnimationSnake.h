#ifndef ANIMATIONSNAKE_H
#define ANIMATIONSNAKE_H

#include "Animation.h"
#include "Achojoao_Nesduino.h"

class AnimationSnake: public Animation {
  
public:

  AnimationSnake() {}
    
  ~AnimationSnake() {}

  virtual void start() {  
    resetValues();
  }

  virtual void display() {
    long currentMillis = millis();
    if (currentMillis - lastMillis >= 100) {
      lastMillis = currentMillis;

      // Shift pointer to the next segment
      ptr = nextPtr;
      nextPtr = next(ptr);
    
      Nesduino.drawPixel(x[ptr], y[ptr], HIGH); // Draw the head of the snake
      Nesduino.write(); // Send bitmap to display
    
      //delay(wait);
    
      if ( ! occupied(nextPtr) ) {
        Nesduino.drawPixel(x[nextPtr], y[nextPtr], LOW); // Remove the tail of the snake
      }
    
      for ( int attempt = 0; attempt < 10; attempt++ ) {
    
        // Jump at random one step up, down, left, or right
        switch ( random(4) ) {
        case 0: x[nextPtr] = constrain(x[ptr] + 1, 0, 7); y[nextPtr] = y[ptr]; break;
        case 1: x[nextPtr] = constrain(x[ptr] - 1, 0, 7); y[nextPtr] = y[ptr]; break;
        case 2: y[nextPtr] = constrain(y[ptr] + 1, 0, 7); x[nextPtr] = x[ptr]; break;
        case 3: y[nextPtr] = constrain(y[ptr] - 1, 0, 7); x[nextPtr] = x[ptr]; break;
        }
    
        if ( ! occupied(nextPtr) ) {
          break; // The spot is empty, break out the for loop
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
  int x[8], y[8];
  int ptr, nextPtr;

  void resetValues() {
    Nesduino.clearScreen();
    Nesduino.setIntensity(3);
    lastMillis = 0;    
    randomSeed(analogRead(A0));
  }

  boolean occupied(int ptrA) {
    for ( int ptrB = 0 ; ptrB < 8; ptrB++ ) {
      if ( ptrA != ptrB ) {
        if ( equal(ptrA, ptrB) ) {
          return true;
        }
      }
    }
  
    return false;
  }
  
  int next(int ptr) {
    return (ptr + 1) % 8;
  }
  
  boolean equal(int ptrA, int ptrB) {
    return x[ptrA] == x[ptrB] && y[ptrA] == y[ptrB];
  }

};

#endif
