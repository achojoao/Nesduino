#ifndef GAME_H
#define GAME_H

const int number35[10][15] = {
                              {HIGH,HIGH,HIGH,HIGH,LOW,HIGH,HIGH,LOW,HIGH,HIGH,LOW,HIGH,HIGH,HIGH,HIGH},
                              {LOW,HIGH,LOW,HIGH,HIGH,LOW,LOW,HIGH,LOW,LOW,HIGH,LOW,HIGH,HIGH,HIGH},
                              {HIGH,HIGH,HIGH,LOW,LOW,HIGH,LOW,HIGH,LOW,HIGH,LOW,LOW,HIGH,HIGH,HIGH},
                              {HIGH,HIGH,HIGH,LOW,LOW,HIGH,LOW,HIGH,HIGH,LOW,LOW,HIGH,HIGH,HIGH,HIGH},
                              {HIGH,LOW,HIGH,HIGH,LOW,HIGH,HIGH,HIGH,HIGH,LOW,LOW,HIGH,LOW,LOW,HIGH},
                              {HIGH,HIGH,HIGH,HIGH,LOW,LOW,HIGH,HIGH,HIGH,LOW,LOW,HIGH,HIGH,HIGH,HIGH},
                              {HIGH,HIGH,HIGH,HIGH,LOW,LOW,HIGH,HIGH,HIGH,HIGH,LOW,HIGH,HIGH,HIGH,HIGH},
                              {HIGH,HIGH,HIGH,LOW,LOW,HIGH,LOW,HIGH,LOW,LOW,HIGH,LOW,LOW,HIGH,LOW},
                              {HIGH,HIGH,HIGH,HIGH,LOW,HIGH,HIGH,HIGH,HIGH,HIGH,LOW,HIGH,HIGH,HIGH,HIGH},
                              {HIGH,HIGH,HIGH,HIGH,LOW,HIGH,HIGH,HIGH,HIGH,LOW,LOW,HIGH,HIGH,HIGH,HIGH}
                            };

class Game {
public:
    
  virtual ~Game() {}

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

  void drawNumber(int number) {
    if (number > 99) {
      number = 99;
    }
    Nesduino.clearScreen();    
    for (int j = 0; j < 2; j++) {
      int num;
      if (j == 0) {
        if (number > 9) {
          num = number / 10;  
        } else {
          num = 0;
        }      
      } else if (j == 1) {
        if (number > 9) {
          num = number % 10;  
        } else {
          num = number;
        }
      }
      for (int i = 0; i<15; i++) {
        if ((j*4)+(i%3)>=0) {          
          Nesduino.drawPixel((j*4)+(i%3),2+(i/3),number35[num][i]);
        }
      }
    }
    Nesduino.write();
  }
};

#endif
