#ifndef CLOCKFEATURE_H
#define CLOCKFEATURE_H

#include <TimeLib.h>
#include "Feature.h"
#include "Achojoao_Nesduino.h"

class ClockFeature: public Feature {

const int diceSide[10][9] = {
                              {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW},
                              {LOW,LOW,LOW,LOW,HIGH,LOW,LOW,LOW,LOW},
                              {HIGH,LOW,LOW,LOW,LOW,LOW,LOW,LOW,HIGH},
                              {HIGH,LOW,LOW,LOW,HIGH,LOW,LOW,LOW,HIGH},
                              {HIGH,LOW,HIGH,LOW,LOW,LOW,HIGH,LOW,HIGH},
                              {HIGH,LOW,HIGH,LOW,HIGH,LOW,HIGH,LOW,HIGH},
                              {HIGH,LOW,HIGH,HIGH,LOW,HIGH,HIGH,LOW,HIGH},
                              {HIGH,LOW,HIGH,HIGH,HIGH,HIGH,HIGH,LOW,HIGH},
                              {HIGH,LOW,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH},
                              {HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH}
                            };
                            
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

public:

  ClockFeature() {
    resetValues();
  }
    
  ~ClockFeature() {}

  virtual void setup() {  
  }

  virtual void loop() {
    if (displayTime) {
      showTime();
      delay(100);
    }
  }

  virtual void showIntro() {
    Nesduino.scrollText("Clock");
  }

  virtual void start() {
    displayTime = true;
  }

  virtual void finish() {
    resetValues();
  }
   
  virtual void aPressed() {
    if (clockMode == 4) {
        setMode++;
        if (setMode > 5) {
          setMode = 0;
        }
    } else {
      scrollTime();
    }
  }

  virtual void bPressed() {
    resetValues();
    displayTime = true;   
    scrollTime();
  }

  virtual void upPressed() {
    if (setMode >= 0) {
      changeTime(true);
    }
  }

  virtual void downPressed() {
    if (setMode >= 0) {
      changeTime(false);
    }
  }

  virtual void leftPressed() {
    if (setMode == -1) {
      clockMode--;
      if (clockMode < 0) {
        clockMode = 4;
      }
    }
  }

  virtual void rightPressed() {
    if (setMode == -1) {
      clockMode++;
      if (clockMode > 4) {
        clockMode = 0;
      }
    }
  }

  void scrollTime() {
    Nesduino.clearScreen();
    Nesduino.scrollText(formatTime(hour()) + ":" + formatTime(minute()));
    delay(500);
    Nesduino.scrollText(String(day()) + "/" + String(month())+ "/" + String(year()));
    delay(500);
  }
  
private:
  
  int clockMode;
  int setMode;
  boolean displayTime;
  boolean lastUpdateAnimationFrame;
  long lastUpdateAnimationMillis;

  void resetValues() {
    clockMode = 0;
    setMode = -1;
    displayTime = false;
    lastUpdateAnimationFrame = false;
    lastUpdateAnimationMillis = 0;
  }
  
  void showTime() {
    if (clockMode != 4 || setMode > -1) {
      Nesduino.clearScreen();
    }
    switch (clockMode) {
      case 0:
        showBinaryTime();
        break;
      case 1:
        showBinaryTime2();
        break;
      case 2:
        showDiceTime();
        break;
      case 3:
        showDiceTime2();
        break; 
      case 4:
        showChangeTime();
        break;  
      }
  }

  String formatTime(int number) {
    if (number < 10) {
      return "0" + String(number);    
    } else {
      return String(number);
    }
  }

  void showDiceTime() {
    showDice(0,hour()/10);
    showDice(1,hour()<10 ? hour() : hour()-((hour()/10)*10));
    showDice(2,minute()/10);
    showDice(3,minute()<10 ? minute() : minute()-((minute()/10)*10));
  }

  void showDiceTime2() {
    showDice(0,minute()/10);
    showDice(1,minute()<10 ? minute() : minute()-((minute()/10)*10));
    showDice(2,second()/10);
    showDice(3,second()<10 ? second() : second()-((second()/10)*10));
  }

  void showDice(int position, int number) {
    int x = (position % 2) * 5;
    int y = (position / 2) * 5;
    for (int i=0; i<9; i++) {
      Nesduino.drawPixel(x+(i%3),y+(i/3),diceSide[number][i]);  
    }
    Nesduino.write();
  }
  
  void showBinaryTime() {
    showBinaryColumn(0,hour()/10);
    showBinaryColumn(1,hour()<10 ? hour() : hour()-((hour()/10)*10));
    showBinaryColumn(2,minute()/10);
    showBinaryColumn(3,minute()<10 ? minute() : minute()-((minute()/10)*10));
    showBinaryColumn(4,second()/10);
    showBinaryColumn(5,second()<10 ? second() : second()-((second()/10)*10));
  }

  void showBinaryColumn(int position, int number) {
    int x = position + (position / 2);
    for (int i=0; i<4; i++) {
      if (bitRead(number, i) == 1) {
        Nesduino.drawPixel(x,7-i,HIGH);
      }
    }
    Nesduino.write();
  }

  void showBinaryTime2() {
    showBinaryColumn2(0,hour());
    showBinaryColumn2(1,minute());
    showBinaryColumn2(2,second());
  }

  void showBinaryColumn2(int position, int number) {
    int x0 = position *3;
    int x1 = x0 + 1;
    for (int i=0; i<8; i++) {
      if (bitRead(number, i) == 1) {
        Nesduino.drawPixel(x0,7-i,HIGH);
        Nesduino.drawPixel(x1,7-i,HIGH);
      }
    }
    Nesduino.write();
  }

  void showChangeTime() {
    if (setMode>-1){
      Nesduino.drawLine(1,0,6,0,HIGH);
      if (second()%2 == 0) {
        Nesduino.drawPixel(setMode+1,0,LOW);
      }
      Nesduino.write();
    }
    switch (setMode) {
      case -1:
        showUpdateAnimation();
        break;
      case 0:
        drawNumber(0,hour()/10);
        drawNumber(1,hour()<10 ? hour() : hour()-((hour()/10)*10));
        break;
      case 1:
        drawNumber(0,minute()/10);
        drawNumber(1,minute()<10 ? minute() : minute()-((minute()/10)*10));
        break;  
      case 2:
        drawNumber(0,second()/10);
        drawNumber(1,second()<10 ? second() : second()-((second()/10)*10));
        break;  
      case 3:
        drawNumber(0,day()/10);
        drawNumber(1,day()<10 ? day() : day()-((day()/10)*10));
        break;  
      case 4:
        drawNumber(0,month()/10);
        drawNumber(1,month()<10 ? month() : month()-((month()/10)*10));
        break;
      case 5:
        drawNumber(0,(year()%100)/10);
        drawNumber(1,(year()%100)<10 ? (year()%100) : (year()%100)-(((year()%100)/10)*10));
        break;    
    }
    Nesduino.write();
  }

  void showUpdateAnimation() { 
    if (millis()-lastUpdateAnimationMillis >= 220) {
      Nesduino.fillScreen(LOW);
      if (lastUpdateAnimationFrame) {
        Nesduino.drawLine(1,1,6,1,HIGH);      
        Nesduino.drawLine(6,1,6,4,HIGH);
        Nesduino.drawLine(5,3,7,3,HIGH);      
        Nesduino.drawLine(6,6,1,6,HIGH);
        Nesduino.drawLine(1,6,1,3,HIGH);
        Nesduino.drawLine(0,4,2,4,HIGH);  
      } else {
        Nesduino.drawLine(1,6,1,1,HIGH);      
        Nesduino.drawLine(1,1,4,1,HIGH);
        Nesduino.drawLine(3,0,3,2,HIGH);      
        Nesduino.drawLine(6,1,6,6,HIGH);
        Nesduino.drawLine(6,6,3,6,HIGH);
        Nesduino.drawLine(4,5,4,7,HIGH); 
      }
      lastUpdateAnimationFrame = !lastUpdateAnimationFrame;
      lastUpdateAnimationMillis = millis();
      Nesduino.write();
    }
  }

  void changeTime(boolean positive) {
    int sign = positive ? 1 : -1;
    switch (setMode) {
        case 0:
          adjustTime(sign * 3600);
          break;
        case 1:
          adjustTime(sign * 60);
          break;
        case 2:
          adjustTime(sign);
          break;
        case 3:
          setTime(hour(),minute(),second(),day()+sign, month(), year());
          break;
        case 4:
          setTime(hour(),minute(),second(),day(),month()+sign, year());
          break;
        case 5:
          setTime(hour(),minute(),second(),day(),month(), year()+sign);
          break;  
      }
  }
  
  void drawNumber(int position, int number) {
    int x = 1 + (position*4);
    int y = 2;
    for (int i = 0; i<15; i++) {
      Nesduino.drawPixel(x+(i%3),y+(i/3),number35[number][i]);   
    }
    Nesduino.write();
  }

};

#endif
