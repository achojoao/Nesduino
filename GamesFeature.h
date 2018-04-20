#ifndef GamesFeature_H
#define GamesFeature_H

#include "Feature.h"
#include "Achojoao_Nesduino.h"

#include "GameSnake.h"
#include "GameFlappy.h"
#include "GameCatMice.h"
#include "GameSimon.h"
#include "GameDice.h"

class GamesFeature: public Feature {
  
public:
  GamesFeature() {}
    
  ~GamesFeature() {}

  virtual void setup() {  
  }

  virtual void loop() {
    if (gameSelected) {
      games[currentGame]->loop();
    } else if (selectionStarted) {
      games[currentGame]->showIntro();
    }
  }

  virtual void start() {  
    gameSelected = false;  
    selectionStarted = true;
  }

  virtual void finish(){
    gameSelected = false;
    selectionStarted = false;
    for (int i = 0; i < NUM_GAMES; i++) {
      games[i]->finish();
    }
  }

  virtual void showIntro() {
    Nesduino.scrollText("Games");
  }
  
  virtual void aPressed() {
    if (gameSelected) {
      games[currentGame]->aPressed();
    } else {
      gameSelected = true;
      games[currentGame]->start();
    }
  }

  virtual void bPressed() {
    games[currentGame]->bPressed();
  }

  virtual void upPressed() {
    games[currentGame]->upPressed();
  }

  virtual void downPressed() {    
    games[currentGame]->downPressed();
  }

  virtual void leftPressed() {
    if (gameSelected) {
      games[currentGame]->leftPressed();
    } else {
      games[currentGame]->finish();
      currentGame--;      
      if (currentGame < 0) {
        currentGame = NUM_GAMES-1;
      }
    }
  }

  virtual void rightPressed() {
    if (gameSelected) {
      games[currentGame]->rightPressed();
    } else {
      games[currentGame]->finish();
      currentGame++;
      if (currentGame == NUM_GAMES) {
        currentGame = 0;
      }
    }
  }

  void showAnimation() {
  }
    
private:

  static const int NUM_GAMES = 5;
  boolean gameSelected = false;
  boolean selectionStarted = false;

  GameSnake gameSnake;
  GameFlappy gameFlappy;
  GameCatMice gameCatMice;
  GameSimon gameSimon;
  GameDice gameDice;
  int currentGame = 0;
  Game* games[NUM_GAMES] = {
    &gameSnake,
    &gameFlappy,    
    &gameCatMice,
    &gameSimon,        
    &gameDice
  };
};

#endif
