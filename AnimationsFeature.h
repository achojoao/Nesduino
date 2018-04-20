#ifndef ANIMATIONSFEATURE_H
#define ANIMATIONSFEATURE_H

#include "Feature.h"
#include "Achojoao_Nesduino.h"
#include "Animation.h"
#include "AnimationDizzy.h"
#include "AnimationEye.h"
#include "AnimationFill.h"
#include "AnimationFire.h"
#include "AnimationFly.h"
#include "AnimationGOL.h"
#include "AnimationHeart.h"
#include "AnimationMatrix.h"
#include "AnimationSnake.h"
#include "AnimationSpinner.h"

class AnimationsFeature: public Feature {
  
public:
  AnimationsFeature() {
  }
    
  ~AnimationsFeature() {}

  virtual void setup() {  
  }

  virtual void loop() {
    if (selectionStarted) {
      animations[currentAnimation]->display();
    }
  }

  virtual void start() {
    selectionStarted = true;  
  }

  virtual void finish(){
    selectionStarted = false;
    for (int i = 0; i < NUM_ANIMATIONS; i++) {
      animations[i]->finish();
    }
  }

  virtual void showIntro() {
    Nesduino.scrollText("Animations");    
  }
  
  virtual void aPressed() {
  }

  virtual void bPressed() {
  }

  virtual void upPressed() {
  }

  virtual void downPressed() {
  }

  virtual void leftPressed() {
    currentAnimation--;
    if (currentAnimation < 0) {
      currentAnimation = NUM_ANIMATIONS-1;
    }
    animations[currentAnimation]->start();
  }

  virtual void rightPressed() {
    currentAnimation++;
    if (currentAnimation == NUM_ANIMATIONS) {
      currentAnimation = 0;
    }
    animations[currentAnimation]->start();
  }

  void showAnimation() {
  }
    
private:

  boolean selectionStarted = false;
  static const int NUM_ANIMATIONS = 10;

  AnimationDizzy animationDizzy;
  AnimationEye animationEye;
  AnimationFill animationFill;
  AnimationFire animationFire;
  AnimationFly animationFly;
  AnimationGOL animationGOL;
  AnimationHeart animationHeart;
  AnimationMatrix animationMatrix;
  AnimationSnake animationSnake;
  AnimationSpinner animationSpinner;
  int currentAnimation = 0;
  Animation* animations[NUM_ANIMATIONS] = {
    &animationDizzy,
    &animationEye,
    &animationFill,
    &animationFire,
    &animationFly,
    &animationGOL,
    &animationHeart,
    &animationMatrix,
    &animationSnake,
    &animationSpinner
  };
   
};

#endif
