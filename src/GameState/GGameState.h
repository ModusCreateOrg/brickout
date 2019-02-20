#ifndef GENUS_GGAMESTATE_H
#define GENUS_GGAMESTATE_H

#include "Game.h"

class GPaddleProcess;

class GGameState : public BGameEngine {
public:
  GGameState();
  ~GGameState();
  void PostRender();
public:
  void Death();
private:
  BFont *mFont8, *mFont16;
  GPaddleProcess *mPaddleProcess;
public:
  TBCD mScore;
  TBCD mLives;
};


#endif //GENUS_GGAMESTATE_H
