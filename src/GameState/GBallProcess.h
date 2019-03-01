#ifndef GENUS_GBALLPROCESS_H
#define GENUS_GBALLPROCESS_H

#include "Game.h"

class GBallProcess : public BProcess {
public:
  GBallProcess(GGameState *aGameState, TFloat aVelocity = 3.5);
  virtual ~GBallProcess();
public:
  TBool RunBefore();
  TBool RunAfter();
public:
  // reposition the ball at start of round
  void Reset(TFloat aVelocity);
  void Reset() {
    Reset(mVelocity);
  }
private:
  BSprite *mSprite;
  TFloat mVelocity;
  GGameState *mGameState;
};

#endif //GENUS_GBALLPROCESS_H
