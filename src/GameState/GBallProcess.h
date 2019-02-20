#ifndef GENUS_GBALLPROCESS_H
#define GENUS_GBALLPROCESS_H

#include "Game.h"

class GBallProcess : public BProcess {
public:
  GBallProcess(BGameEngine *aGameEngine, TFloat aVelocity = 3.5);
  virtual ~GBallProcess();
public:
  TBool RunBefore();
  TBool RunAfter();
public:
  // reposition the ball at start of round
  void Reset(TFloat aVelocity);
private:
  BSprite *mSprite;
  TFloat mVelocity;
};

#endif //GENUS_GBALLPROCESS_H
