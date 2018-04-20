#ifndef ACHOJOAO_NESDUINO_H
#define ACHOJOAO_NESDUINO_H

#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

#define RANDOM_PIN    A0
#define SPEAKER_PIN   D0
#define SPEAKER_G_PIN D1
#define NES_LATCH_PIN D2
#define NES_CLOCK_PIN D3
#define NES_DATA_PIN  D4
#define MATRIX_PIN    D6

#define A_BUTTON      0
#define B_BUTTON      1
#define SELECT_BUTTON 2
#define START_BUTTON  3
#define UP_BUTTON     4
#define DOWN_BUTTON   5
#define LEFT_BUTTON   6
#define RIGHT_BUTTON  7

class Achojoao_Nesduino {
 public:
 
  void begin();

  //Controller
  byte readKeys();
  boolean aPressed(byte keys);
  boolean bPressed(byte keys);
  boolean upPressed(byte keys);
  boolean downPressed(byte keys);
  boolean leftPressed(byte keys);
  boolean rightPressed(byte keys);

  //Speaker
  void playTone(int note, int duration, boolean wait);

  //Matrix
  void setIntensity(int intensity){matrix.setIntensity(intensity);}
  void setRotation(int rotation){matrix.setRotation(rotation);}
  void drawPixel(int x, int y, int value){matrix.drawPixel(x,y,value);}
  void drawChar(char letter) {matrix.drawChar(1, 0, (unsigned char)letter, HIGH, LOW, 1);matrix.write();}
  void drawLine(int x0, int y0, int x1, int y1, int color) {matrix.drawLine(x0, y0, x1, y1, color);}
  void drawCircle(int x, int y, int radius, int color) {matrix.drawCircle(x, y, radius, color);}
  void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t radius, uint16_t color) {matrix.fillRoundRect(x,y,w,h,radius,color);}
  void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,int16_t x2, int16_t y2, uint16_t color) {matrix.fillTriangle(x0,y0,x1,y1,x2,y2,color);}
  void scrollText(String text);
  void fillScreen(int value) {matrix.fillScreen(value);}
  void clearScreen(){matrix.fillScreen(LOW);matrix.write();}  
  void write(){matrix.write();}

 private:

  Max72xxPanel matrix = Max72xxPanel(MATRIX_PIN, 1, 1);
  boolean keyPressed = false;

};

extern Achojoao_Nesduino Nesduino;

#endif
