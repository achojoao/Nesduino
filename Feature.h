#ifndef FEATURE_H
#define FEATURE_H

class Feature {
public:
    
  virtual ~Feature() {}

  virtual void setup() = 0;
  virtual void loop() = 0;
  virtual void start() = 0;
  virtual void finish() = 0;
  virtual void showIntro() = 0;
  virtual void aPressed() = 0;
  virtual void bPressed() = 0;
  virtual void upPressed() = 0;
  virtual void downPressed() = 0;
  virtual void leftPressed() = 0;
  virtual void rightPressed() = 0;

};

#endif
