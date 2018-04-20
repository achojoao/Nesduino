#include "Achojoao_Nesduino.h"

void Achojoao_Nesduino::begin() {
  
  //Speaker
  pinMode(SPEAKER_PIN, OUTPUT);
  digitalWrite(SPEAKER_PIN, LOW);
  pinMode(SPEAKER_G_PIN, OUTPUT);
  digitalWrite(SPEAKER_G_PIN, LOW);

  //Nes controller
  pinMode(NES_DATA_PIN, INPUT);
  pinMode(NES_CLOCK_PIN, OUTPUT);
  pinMode(NES_LATCH_PIN, OUTPUT);
  digitalWrite(NES_CLOCK_PIN, LOW);
  digitalWrite(NES_LATCH_PIN, LOW);
  
  //Matrix
  matrix.setIntensity(4);
  matrix.setRotation(0);

  randomSeed(analogRead(RANDOM_PIN)); // initialize random generator
  
}

void Achojoao_Nesduino::playTone(int note, int duration, boolean wait) {
  if (note>0) tone(SPEAKER_PIN,note,duration);
  if (wait) delay(duration);
}

byte Achojoao_Nesduino::readKeys() {  
  keyPressed = false;
  int tempData = 255;
  
  digitalWrite(NES_LATCH_PIN, HIGH);
  delayMicroseconds(12);
  digitalWrite(NES_LATCH_PIN, LOW);
  delayMicroseconds(12);
 
  if (digitalRead(NES_DATA_PIN) == LOW)
    bitClear(tempData, A_BUTTON);
    
  digitalWrite(NES_CLOCK_PIN, HIGH);
  delayMicroseconds(6);
  digitalWrite(NES_CLOCK_PIN, LOW);
  delayMicroseconds(6);
  if (digitalRead(NES_DATA_PIN) == LOW)
    bitClear(tempData, B_BUTTON);
  
  digitalWrite(NES_CLOCK_PIN, HIGH);
  delayMicroseconds(6);
  digitalWrite(NES_CLOCK_PIN, LOW);
  delayMicroseconds(6);
  if (digitalRead(NES_DATA_PIN) == LOW)
    bitClear(tempData, SELECT_BUTTON);

  digitalWrite(NES_CLOCK_PIN, HIGH);
  delayMicroseconds(6);
  digitalWrite(NES_CLOCK_PIN, LOW);
  delayMicroseconds(6);
  if (digitalRead(NES_DATA_PIN) == LOW)
    bitClear(tempData, START_BUTTON);

  digitalWrite(NES_CLOCK_PIN, HIGH);
  delayMicroseconds(6);
  digitalWrite(NES_CLOCK_PIN, LOW);
  delayMicroseconds(6);
  if (digitalRead(NES_DATA_PIN) == LOW)
    bitClear(tempData, UP_BUTTON);
    
  digitalWrite(NES_CLOCK_PIN, HIGH);
  delayMicroseconds(6);
  digitalWrite(NES_CLOCK_PIN, LOW);
  delayMicroseconds(6);
  if (digitalRead(NES_DATA_PIN) == LOW)
    bitClear(tempData, DOWN_BUTTON);

  digitalWrite(NES_CLOCK_PIN, HIGH);
  delayMicroseconds(6);
  digitalWrite(NES_CLOCK_PIN, LOW);
  delayMicroseconds(6);
  if (digitalRead(NES_DATA_PIN) == LOW)
    bitClear(tempData, LEFT_BUTTON);  
    
  digitalWrite(NES_CLOCK_PIN, HIGH);
  delayMicroseconds(6);
  digitalWrite(NES_CLOCK_PIN, LOW);
  delayMicroseconds(6);
  if (digitalRead(NES_DATA_PIN) == LOW)
    bitClear(tempData, RIGHT_BUTTON);
    
  return tempData;
}

boolean Achojoao_Nesduino::aPressed(byte keys) {
  keyPressed = (bitRead(keys, A_BUTTON) == 0);
  return keyPressed;
}

boolean Achojoao_Nesduino::bPressed(byte keys) {
  keyPressed = (bitRead(keys, B_BUTTON) == 0);
  return keyPressed;
}

boolean Achojoao_Nesduino::upPressed(byte keys) {
  keyPressed = (bitRead(keys, UP_BUTTON) == 0);
  return keyPressed;
}

boolean Achojoao_Nesduino::downPressed(byte keys) {
  keyPressed = (bitRead(keys, DOWN_BUTTON) == 0);
  return keyPressed;
}

boolean Achojoao_Nesduino::leftPressed(byte keys) {
  keyPressed = (bitRead(keys, LEFT_BUTTON) == 0);
  return keyPressed;
}

boolean Achojoao_Nesduino::rightPressed(byte keys) {
  keyPressed = (bitRead(keys, RIGHT_BUTTON) == 0);
  return keyPressed;
}

void Achojoao_Nesduino::scrollText(String text) { 
  int width = 6;
  int spacer = 1;
  long firstTime = millis();
  for (int i = 0; i < width * text.length() + matrix.width() - 1 - spacer; i++) {
    matrix.fillScreen(LOW);
    int letter = i / width;
    int x = (matrix.width() - 1) - i % width;
    int y = (matrix.height() - 8) / 2;
    while (x + width - spacer >= 0 && letter >= 0) {
       if (letter < text.length()) {
          matrix.drawChar(x, y, text[letter], HIGH, LOW, 1);
       }
       letter--;
       x -= width;
    }
    matrix.write();
    delay(50);
    if (millis() - firstTime >= 500) {
      byte keys = readKeys();
      if (keys < 255) {
        break;
      }
    }
   }
   matrix.fillScreen(LOW);
   matrix.write();
}

Achojoao_Nesduino Nesduino;
