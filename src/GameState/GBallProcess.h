#ifndef GENUS_GBALLPROCESS_H
#define GENUS_GBALLPROCESS_H

#include "Game.h"

class GBallProcess : public BProcess {
public:
  GBallProcess(BGameEngine *aGameEngine);
  virtual ~GBallProcess();
public:
  TBool RunBefore();
  TBool RunAfter();
public:
  // reposition the ball at start of round
  void Reset(TFloat aVelocity = 2.5);
private:
  BSprite *mSprite;
};


#endif //GENUS_GBALLPROCESS_H
