#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
#include <TimeLib.h>
#include "Tone.h"
#include "Achojoao_Nesduino.h"
#include "Feature.h"
#include "AlarmFeature.h"
#include "AnimationsFeature.h"
#include "ClockFeature.h"
#include "GamesFeature.h"
#include "TestFeature.h"

AlarmFeature alarmFeature;
AnimationsFeature animationsFeature;
ClockFeature clockFeature;
GamesFeature gamesFeature;
TestFeature testFeature;

boolean menuMode = true;
int currentFeature = -1;
Feature* features[] = {
  &gamesFeature,
  &animationsFeature, 
  &alarmFeature,
  &clockFeature,   
  &testFeature  
};

const int NUM_FEATURES = (sizeof(features)/sizeof(Feature*));

void setup() {

  Serial.begin(9600);
  Serial.println("Nesduino by achojoao");

  Nesduino.begin();

  setTime(0,0,0,1,1,2018);

  showIntro();

  for (int i = 0; i < NUM_FEATURES; i++) {
      features[i]->setup();
  }

}

void loop() {

  alarmFeature.isAlarmTime(hour(),minute(),weekday());  

  byte keys = Nesduino.readKeys();

  if (Nesduino.aPressed(keys) && Nesduino.bPressed(keys)) {
    features[currentFeature]->finish();
    showMenu();
    currentFeature = -1;
    menuMode = true;
  } else {
    if (Nesduino.aPressed(keys)) {
      if (currentFeature >= 0 && menuMode) {
        showSelection();
        menuMode = false;
        features[currentFeature]->start();
      } else if (menuMode) { 
        clockFeature.scrollTime();
        menuAnimation();
      } else if(!menuMode) {
        features[currentFeature]->aPressed();
      }
    }
    if (Nesduino.bPressed(keys)) {
      if (menuMode && currentFeature == -1) {  
        clockFeature.scrollTime();
        menuAnimation();
      } else {
        features[currentFeature]->bPressed();
      }
    }
    if (Nesduino.upPressed(keys)) {
      if (!menuMode) features[currentFeature]->upPressed();
    }  
    if (Nesduino.downPressed(keys)) {
      if (!menuMode) features[currentFeature]->downPressed();
    } 
    if (Nesduino.leftPressed(keys)) {
      if (menuMode) {
        currentFeature--;
        if (currentFeature < 0) {
          currentFeature = NUM_FEATURES-1;
        }
        features[currentFeature]->showIntro();
      } else {
        features[currentFeature]->leftPressed();
      }
    }
    if (Nesduino.rightPressed(keys)) {
      if (menuMode) {
        currentFeature++;
        if (currentFeature >= NUM_FEATURES) {
          currentFeature = 0;
        }
        features[currentFeature]->showIntro();
      } else {
        features[currentFeature]->rightPressed();
      }
    }
  
  }
  delay(60);
  if (currentFeature>=0) features[currentFeature]->loop();
  
}

void showIntro() {
  introAnimation();
  delay(200);
  introSound();
  delay(2000);
  menuAnimation();
}

void introAnimation() {
  for (int i=0; i<9; i++) {
    delay(250);
    Nesduino.fillScreen(LOW);
    Nesduino.drawPixel(5,i-4, HIGH);
    Nesduino.drawPixel(6,i-4, HIGH);
    Nesduino.drawPixel(2,i-3, HIGH);
    Nesduino.drawPixel(2,i-5, HIGH);
    Nesduino.drawPixel(1,i-4, HIGH);
    Nesduino.drawPixel(3,i-4, HIGH);
    Nesduino.write();
  }
}

void introSound() {
  Nesduino.playTone(NOTE_B6,100,true);
  Nesduino.playTone(0,100,true);
  Nesduino.playTone(NOTE_E7,550,true);
}

void showSelection() {
  selectionAnimation();
  selectionSound();
  delay(500);
}

void selectionAnimation() {
  for (int i=3; i>=0; i--) {
    Nesduino.fillScreen(LOW);
    Nesduino.drawPixel(i,i, HIGH);
    Nesduino.drawPixel(7-i,i, HIGH);
    Nesduino.drawPixel(i,7-i, HIGH);
    Nesduino.drawPixel(7-i,7-i, HIGH);
    Nesduino.write();
    delay(60);
  }
  Nesduino.fillScreen(LOW);
  Nesduino.write();
}

void selectionSound() {
  Nesduino.playTone(NOTE_B6,100,true);
}

void showMenu() {
  menuAnimation();
  menuSound();
  delay(500);
}

void menuAnimation() {
  for (int i=0; i<4; i++) {
    Nesduino.fillScreen(LOW);
    Nesduino.drawPixel(i,i, HIGH);
    Nesduino.drawPixel(7-i,i, HIGH);
    Nesduino.drawPixel(i,7-i, HIGH);
    Nesduino.drawPixel(7-i,7-i, HIGH);
    Nesduino.write();
    delay(60);
  }
}

void menuSound() {
  Nesduino.playTone(NOTE_A5,100,true);
}
