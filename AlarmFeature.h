#ifndef ALARMFEATURE_H
#define ALARMFEATURE_H

#include "Feature.h"
#include "Achojoao_Nesduino.h"

const int MAX_ALARM = 3;
const int SNOOZE_MINUTES = 10;

int alarmMelody[] = { }; 
int alarmNoteDurations[] = {};

struct melody {
  int alarmSize;
  int notes[150];
  double durations[134];
} melodies[] = {    
  { 134, // Mario Bros
    {NOTE_E7,NOTE_E7,0,NOTE_E7,0,NOTE_C7,NOTE_E7,0,NOTE_G7,0,0, 0,NOTE_G6,0,0,0,NOTE_C7,0,0,NOTE_G6,0,0,NOTE_E6,0,0,NOTE_A6,0,NOTE_B6,0,NOTE_AS6,NOTE_A6,0,NOTE_G6,NOTE_E7,NOTE_G7,NOTE_A7,0,NOTE_F7,NOTE_G7,0,NOTE_E7,0,NOTE_C7,NOTE_D7,NOTE_B6,0,0,NOTE_C7,0,0,NOTE_G6,0,0,NOTE_E6,0,0,NOTE_A6,0,NOTE_B6,0,NOTE_AS6,NOTE_A6,0,NOTE_G6,NOTE_E7,NOTE_G7,NOTE_A7,0,NOTE_F7,NOTE_G7,0,NOTE_E7,0,NOTE_C7,NOTE_D7,NOTE_B6,0,0,NOTE_C4,NOTE_C5,NOTE_A3,NOTE_A4,NOTE_AS3,NOTE_AS4,0,0,NOTE_C4,NOTE_C5,NOTE_A3,NOTE_A4,NOTE_AS3,NOTE_AS4,0,0,NOTE_F3,NOTE_F4,NOTE_D3,NOTE_D4,NOTE_DS3,NOTE_DS4,0,0,NOTE_F3,NOTE_F4,NOTE_D3,NOTE_D4,NOTE_DS3,NOTE_DS4,0,0,NOTE_DS4,NOTE_CS4,NOTE_D4,NOTE_CS4,NOTE_DS4,NOTE_DS4,NOTE_GS3,NOTE_G3,NOTE_CS4,NOTE_C4,NOTE_FS4,NOTE_F4,NOTE_E3,NOTE_AS4,NOTE_A4,NOTE_GS4,NOTE_DS4,NOTE_B3,NOTE_AS3,NOTE_A3,NOTE_GS3,0,0,0},
    {12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,9,9,9,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,9,9,9,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,6,3,12,12,12,12,12,12,6,3,12,12,12,12,12,12,6,3,12,12,12,12,12,12,6,6,18,18,18,6,6,6,6,6,6,18,18,18,18,18,18,10,10,10,10,10,10,3,3,3}
  },
  { 61, // Indiana Jones
    {NOTE_E5,0,NOTE_F5,NOTE_G5,0,NOTE_C6,0,NOTE_D5,0,NOTE_E5,NOTE_F5,0,NOTE_G5,0,NOTE_A5,NOTE_B5,0,NOTE_F6,0,NOTE_A5,0,NOTE_B5,NOTE_C6,NOTE_D6,NOTE_E6,NOTE_E5,0,NOTE_F5,NOTE_G5,0,NOTE_C6,0,NOTE_D6,0,NOTE_E6,NOTE_F6,0,NOTE_G5,0,NOTE_G5,NOTE_E6,0,NOTE_D6,0,NOTE_G5,NOTE_E6,0,NOTE_D6,0,NOTE_G5,NOTE_E6,0,NOTE_D6,0,NOTE_G5,NOTE_F6,0,NOTE_E6,0,NOTE_D6,NOTE_C6}, 
    {8,16,16,16,16,2,8,8,16,16,2,4,8,16,16,16,16,2,8,8,16,16,4,4,4,8,16,16,16,16,2,8,8,16,16,2,4,8,16,16,8,8,8,16,16,8,8,8,16,16,8,8,8,16,16,8,8,8,16,16,2}
  },
  { 46, // Star Wars
    {NOTE_G4,NOTE_G4,NOTE_G4,NOTE_DS4,NOTE_AS4,NOTE_G4,NOTE_DS4,NOTE_AS4,NOTE_G4,NOTE_D5,NOTE_D5,NOTE_D5,NOTE_DS5,NOTE_AS4,NOTE_FS4,NOTE_DS4,NOTE_AS4,NOTE_G4,NOTE_G5,NOTE_G4,NOTE_G4,NOTE_G5,NOTE_FS5,NOTE_F5,NOTE_E5,NOTE_DS5,NOTE_E5,0,NOTE_G4,0,NOTE_CS5,NOTE_C5,NOTE_B4,NOTE_AS4,NOTE_A4,NOTE_AS4,0,NOTE_DS4,0,NOTE_FS4,NOTE_DS4,NOTE_AS4,NOTE_G4,NOTE_DS4,NOTE_AS4,NOTE_G4},
    {3,3,3,4.5,12,3,4.5,12,1.5,3,3,3,4.5,12,3,4.5,12,1.5,3,4.5,12,3,4.5,12,12,12,12,4.5,12,12,3,4.5,12,12,12,12,4.5,12,12,3,4.5,12,3,4.5,12,1.5}    
  },    
  { 97, // Legend Of Zelda
    {NOTE_AS5,NOTE_F5,NOTE_AS5,NOTE_AS5,NOTE_C6,NOTE_D6,NOTE_DS6,NOTE_F6,0,NOTE_F6,NOTE_F5,NOTE_FS6,NOTE_GS5,NOTE_AS5,NOTE_AS5,NOTE_GS6,NOTE_FS5,NOTE_GS5,NOTE_FS5,NOTE_F6,NOTE_F6,NOTE_DS6,NOTE_DS6,NOTE_F6,NOTE_FS6,NOTE_F6,NOTE_DS6,NOTE_CS6,NOTE_CS6,NOTE_DS6,NOTE_F6,NOTE_DS6,NOTE_CS6,NOTE_C6,NOTE_C6,NOTE_D6,NOTE_E6,NOTE_G6,NOTE_F6,NOTE_F5,NOTE_F5,NOTE_F5,NOTE_F5,NOTE_F5,NOTE_F5,NOTE_F5,NOTE_F5,NOTE_F5,NOTE_F5,NOTE_AS5,NOTE_F5,NOTE_AS5,NOTE_AS5,NOTE_C6,NOTE_D6,NOTE_DS6,NOTE_F6,0,NOTE_F6,NOTE_F5,NOTE_FS6,NOTE_GS5,NOTE_AS5,NOTE_CS7,NOTE_C7,NOTE_A6,NOTE_F6,NOTE_FS5,NOTE_AS6,NOTE_A6,NOTE_F6,NOTE_F6,NOTE_FS5,NOTE_AS6,NOTE_A6,NOTE_F6,NOTE_D6,NOTE_DS5,NOTE_FS6,NOTE_F6,NOTE_CS6,NOTE_AS5,NOTE_C6,NOTE_D6,NOTE_E6,NOTE_G6,NOTE_F6,NOTE_F5,NOTE_F5,NOTE_F5,NOTE_F5,NOTE_F5,NOTE_F5,NOTE_F5,NOTE_F5,NOTE_F5,NOTE_F5}, 
    {4,3,8,16,16,16,16,2,8,8,12,16,12,2,12,16,12,6,12,2,6,8,16,16,2,8,8,8,16,16,2,8,8,8,16,16,2,6,8,16,16,8,16,16,8,16,16,8,8,4,3,8,16,16,16,16,3,8,8,12,16,12,2,4,4,2,4,2,4,4,2,4,2,4,4,2,4,2,4,4,2,3,6,16,2,6,8,16,16,8,16,16,8,16,16,8,8}    
  },
};

class AlarmFeature: public Feature {

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
  AlarmFeature() {
    reset();
  }
    
  ~AlarmFeature() {}

  virtual void setup() {  
  }

  virtual void loop() {
  }

  virtual void showIntro() {
    Nesduino.scrollText("Alarm");
  }

  virtual void start() {
    reset();
    displayAlarm();
  }

  virtual void finish(){
    reset();
  }
   
  virtual void aPressed() {
    editMode = true;
    editField++;
    if (editField > 4) {
      editField = 0;
    }
    cleanBottomSection();
    switch(editField) {
        case 0:
          Nesduino.drawLine(2,0,4,0,HIGH);
          Nesduino.drawPixel(6,0,LOW);
          Nesduino.drawLine(1,3,1,6,LOW);                    
          displayTime(0);      
          break;
        case 1:
          Nesduino.drawLine(2,0,4,0,LOW);
          Nesduino.drawPixel(6,0,HIGH);
          Nesduino.drawLine(1,3,1,6,LOW);
          displayTime(0);
          break;
        case 2:
          Nesduino.drawLine(2,0,4,0,LOW);
          Nesduino.drawPixel(6,0,LOW);
          Nesduino.drawLine(1,3,1,6,LOW);
          Nesduino.drawPixel(7,4,HIGH);                    
          Nesduino.drawPixel(7,6,HIGH);                    
          displayTime(0);
          break;
        case 3:
          Nesduino.drawLine(2,0,4,0,LOW);
          Nesduino.drawPixel(6,0,LOW);
          Nesduino.drawPixel(0,4,HIGH);  
          Nesduino.drawPixel(0,6,HIGH);  
          displayTimeGap(0, true);
          break;
        case 4:
          Nesduino.drawLine(2,0,4,0,LOW);
          Nesduino.drawPixel(6,0,LOW);
          Nesduino.drawLine(1,3,1,6,LOW);          
          displayNote();
          Nesduino.drawPixel(1,3+alarms[currentAlarm][2],HIGH);
          break;
      }
      Nesduino.write();
  }

  virtual void bPressed() {
    int aux = currentAlarm;
    reset();
    currentAlarm = aux;
    displayAlarm();
  }

  virtual void upPressed() {
    if (editMode) {
      switch(editField) {
        case 0:
          changeAlarmPeriod();
          break;
        case 1:
          changeSnoozer();
          break;
        case 2:
          changeHour(true);  
          break;
        case 3:
          changeMinute(true);
          break;
        case 4:
          changeMelody(true);
          break;
      }
      Nesduino.write();
    }
  }

  virtual void downPressed() {
    if (editMode) {
      switch(editField) {
        case 0:
          changeAlarmPeriod();
          break;
        case 1:
          changeSnoozer();
          break;
        case 2:
          changeHour(false);
          break;
        case 3:
          changeMinute(false); 
          break;
        case 4:
          changeMelody(false);
          break;
      }
      Nesduino.write();
    }
  }

  virtual void leftPressed() {
    if (!editMode) {
      currentAlarm--;
      if (currentAlarm < 0) {
        currentAlarm = MAX_ALARM - 1;
      }
      displayAlarm();
    }    
  }

  virtual void rightPressed() {
    if (!editMode) {
      currentAlarm++;
      if (currentAlarm == MAX_ALARM) {
        currentAlarm = 0;
      }
      displayAlarm();
    }
  }

  void isAlarmTime(int h, int m, int dayOfWeek) {
    if (alarmRinging > -1) {
      if (m != alarmRinging) {
        alarmRinging = -1;
      }
    } else {
      for (int i = 0; i < MAX_ALARM; i++) {
        if (alarms[i][0] == 3 || (alarms[i][0] == 1 && dayOfWeek >= 2 &&  dayOfWeek <= 6) || (alarms[i][0] == 2 && dayOfWeek == 1 &&  dayOfWeek == 7)) {
          if (alarms[i][3] == h && alarms[i][4] == m) {
            alarmRinging = m;
            playAlarm(i);
            break;
          } else if (alarms[i][1] == 1) {
            int snoozeHour = alarms[i][3];
            int snoozeMinute = alarms[i][4] + SNOOZE_MINUTES;
            if (snoozeMinute >= 60) {
              snoozeHour++;
              if (snoozeHour > 23) {
                snoozeHour = 0;
              }
              snoozeMinute = snoozeMinute - 60;
            }
            if (h == snoozeHour && m == snoozeMinute) {
              alarmRinging = m;
              playAlarm(i);
              break;
            }
          }
        }
      }
    }
  }
  
private:

  int currentAlarm;

  boolean editMode;

  int editField;

  int alarmRinging = -1;
  
  int alarms[MAX_ALARM][5] = {
      {1,1,0,8,0},
      {0,0,1,13,30},
      {0,0,3,17,53},
  };

  void reset() {
    currentAlarm = 0;
    editMode = false;
    editField = -1;
  }

  void displayAlarm() {
    Nesduino.fillScreen(LOW);
    Nesduino.drawPixel(0,currentAlarm,HIGH);
    Nesduino.drawPixel(6,1,alarms[currentAlarm][1]);
    if (alarms[currentAlarm][0] == 1 || alarms[currentAlarm][0] == 3) {
      Nesduino.drawPixel(2,1,HIGH);
      Nesduino.drawPixel(3,1,HIGH);
    }
    if (alarms[currentAlarm][0] == 2 || alarms[currentAlarm][0] == 3) {
      Nesduino.drawPixel(4,1,HIGH);
    }
    Nesduino.write();
    scrollTime();    
  }

  void scrollTime() {
    for (int i=0; i>=-9; i--) {      
      cleanBottomSection();
      displayTime(i);        
      delay(75); 
    }
    delay(300); 
    for (int i=-9; i<=0; i++) {
      cleanBottomSection();
      displayTime(i);  
      delay(75); 
    } 
  }

  void displayTime(int x) {
    displayTimeGap(x,false);
  }

  void displayTimeGap(int x, boolean gap) {
    if (gap) x = x - 9;
    drawNumber(x,alarms[currentAlarm][3]/10);
    int hourUnit = alarms[currentAlarm][3];
    drawNumber(x+4,hourUnit<10 ? hourUnit : hourUnit - ((hourUnit/10)*10));        
    Nesduino.drawPixel(x+8,4,HIGH);
    Nesduino.drawPixel(x+8,6,HIGH);  
    drawNumber(x+10,alarms[currentAlarm][4]/10);   
    int minuteUnit = alarms[currentAlarm][4];
    drawNumber(x+14,minuteUnit<10 ? minuteUnit : minuteUnit - ((minuteUnit/10)*10));   
    Nesduino.write();
  }
  
  void drawNumber(int x, int number) {
    for (int i = 0; i<15; i++) {
      if (x+(i%3)>=0) {
        Nesduino.drawPixel(x+(i%3),3+(i/3),number35[number][i]);
      }
    }
  }

  void displayNote() {
    Nesduino.drawLine(3,3,3,4,HIGH);
    Nesduino.drawLine(5,3,5,5,HIGH);
    Nesduino.drawPixel(2,5,HIGH);
    Nesduino.drawPixel(4,6,HIGH);
    Nesduino.drawPixel(4,3,HIGH);
  }

  void cleanBottomSection() {
    Nesduino.drawLine(0,3,7,3,LOW);
    Nesduino.drawLine(0,4,7,4,LOW);
    Nesduino.drawLine(0,5,7,5,LOW);
    Nesduino.drawLine(0,6,7,6,LOW);
    Nesduino.drawLine(0,7,7,7,LOW);
  }

  void changeAlarmPeriod() {
    alarms[currentAlarm][0]++;
    if (alarms[currentAlarm][0]>3) {
      alarms[currentAlarm][0] = 0;
    }
    Nesduino.drawLine(2,1,4,1,LOW);
    if (alarms[currentAlarm][0] == 1 || alarms[currentAlarm][0] == 3) {
      Nesduino.drawPixel(2,1,HIGH);
      Nesduino.drawPixel(3,1,HIGH);
    }
    if (alarms[currentAlarm][0] == 2 || alarms[currentAlarm][0] == 3) {
      Nesduino.drawPixel(4,1,HIGH);
    }
  }

  void changeSnoozer() {
    alarms[currentAlarm][1]++;
    if (alarms[currentAlarm][1]>1) {
      alarms[currentAlarm][1] = 0;
    }
    Nesduino.drawPixel(6,1,alarms[currentAlarm][1] == 0 ? LOW : HIGH);
  }

  void changeHour(boolean positive) {
    if (positive) {
      alarms[currentAlarm][3]++;
      if (alarms[currentAlarm][3] > 23) {
        alarms[currentAlarm][3] = 0;
      }
    } else {
      alarms[currentAlarm][3]--;
      if (alarms[currentAlarm][3] < 0) {
        alarms[currentAlarm][3] = 23;
      }
    }
    cleanBottomSection();
    Nesduino.drawPixel(7,4,HIGH);  
    Nesduino.drawPixel(7,6,HIGH);  
    drawNumber(0,alarms[currentAlarm][3]/10);   
    int unit = alarms[currentAlarm][3];
    drawNumber(4,unit<10 ? unit : unit - ((unit/10)*10));      
  }

  void changeMinute(boolean positive) {
    if (positive) {
      alarms[currentAlarm][4]++;
      if (alarms[currentAlarm][4] > 59) {
        alarms[currentAlarm][4] = 0;
      }
    } else {
      alarms[currentAlarm][4]--;
      if (alarms[currentAlarm][4] < 0) {
        alarms[currentAlarm][4] = 59;
      }
    }
    cleanBottomSection();
    Nesduino.drawPixel(0,4,HIGH);  
    Nesduino.drawPixel(0,6,HIGH);  
    drawNumber(1,alarms[currentAlarm][4]/10);   
    int unit = alarms[currentAlarm][4];
    drawNumber(5,unit<10 ? unit : unit - ((unit/10)*10));
  }

  void changeMelody(boolean positive) {
    if (positive) {
      alarms[currentAlarm][2]--;
      if (alarms[currentAlarm][2] < 0) {
        alarms[currentAlarm][2] = 3;
      }
    } else {
      alarms[currentAlarm][2]++;
      if (alarms[currentAlarm][2] > 3) {
        alarms[currentAlarm][2] = 0;
      }  
    }    
    Nesduino.drawLine(1,3,1,6,LOW);
    Nesduino.drawPixel(1,3+alarms[currentAlarm][2],HIGH);
    Nesduino.write();
    playAlarm(currentAlarm);
  }

  void playAlarm(int alarm) {
    bool stopAlarm = false;
    int melodyNumber = alarms[alarm][2];
    for (int thisNote = 0; thisNote < melodies[melodyNumber].alarmSize && !stopAlarm; thisNote++) {      
      int noteDuration = 750 / melodies[melodyNumber].durations[thisNote];      
      Nesduino.playTone(melodies[melodyNumber].notes[thisNote], noteDuration, true);  
      Nesduino.playTone(0, noteDuration * 1.30, true);  
      byte keys = Nesduino.readKeys();
      if (Nesduino.aPressed(keys) || Nesduino.bPressed(keys) || Nesduino.upPressed(keys) || Nesduino.downPressed(keys) || Nesduino.leftPressed(keys) || Nesduino.rightPressed(keys)) {
        stopAlarm = true;        
      }
    }
    if (!stopAlarm) {
      alarmRinging = -1;
    }
  }
  
};

#endif
