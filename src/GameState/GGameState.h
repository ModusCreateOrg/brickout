#ifndef GENUS_GGAMESTATE_H
#define GENUS_GGAMESTATE_H

#include "Game.h"

class GPaddleProcess;
class GBallProcess;

class GGameState : public BGameEngine {
public:
  GGameState();
  ~GGameState();
  void PostRender();
public:
  void Reset();
  void Death();
private:
  BFont *mFont8, *mFont16;
  GPaddleProcess *mPaddleProcess;
public:
  TBCD mScore;
  TBCD mLives;
  TBCD mLevel;
  GBallProcess *mBallProcess;
};

#endif //GENUS_GGAMESTATE_H
