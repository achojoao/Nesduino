#ifndef TESTFEATURE_H
#define TESTFEATURE_H

#include "Feature.h"
#include "Achojoao_Nesduino.h"

class TestFeature: public Feature {
  
public:
  TestFeature() {}
    
  ~TestFeature() {}

  virtual void setup() {  
  }

  virtual void loop() {    
  }

  virtual void showIntro() {
    Nesduino.scrollText("Test");
  }

  virtual void start() {
    printKeys();
  }

  virtual void finish(){}
   
  virtual void aPressed() {
    Nesduino.drawPixel(6,4,LOW);
    Nesduino.write();
    delay(50);
    printKeys();
  }

  virtual void bPressed() {
    Nesduino.drawPixel(5,4,LOW);
    Nesduino.write();
    delay(50);
    printKeys();
  }

  virtual void upPressed() {
    Nesduino.drawPixel(2,3,LOW);
    Nesduino.write();
    delay(50);
    printKeys();
  }

  virtual void downPressed() {
    Nesduino.drawPixel(2,5,LOW);
    Nesduino.write();
    delay(50);
    printKeys();
  }

  virtual void leftPressed() {
    Nesduino.drawPixel(1,4,LOW);
    Nesduino.write();
    delay(50);
    printKeys();
  }

  virtual void rightPressed() {
    Nesduino.drawPixel(3,4,LOW);
    Nesduino.write();
    delay(50);
    printKeys();
  }

  void printKeys() {
    Nesduino.fillScreen(LOW);
    Nesduino.drawPixel(5,4,HIGH);
    Nesduino.drawPixel(6,4,HIGH);
    Nesduino.drawPixel(2,3,HIGH);
    Nesduino.drawPixel(2,5,HIGH);
    Nesduino.drawPixel(1,4,HIGH);
    Nesduino.drawPixel(3,4,HIGH);
    Nesduino.write();
  }
  
private:
};

#endif
