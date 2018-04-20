#ifndef ANIMATION_H
#define ANIMATION_H

class Animation {
public:
    
  virtual ~Animation() {}

  virtual void start() = 0;
  virtual void finish() = 0;
  virtual void display() = 0;

};

#endif
