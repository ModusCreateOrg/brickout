#ifndef GENUS_GPADDLEPROCESS_H
#define GENUS_GPADDLEPROCESS_H

#include "Game.h"
class GGameState;

class GPaddleProcess : public BProcess {
public:
  GPaddleProcess(GGameState *aGameState);
  ~GPaddleProcess();
public:
  void Reset();
public:
  TBool RunBefore();
  TBool RunAfter();
protected:
  BSprite *mSprite;
  GGameState *mGameState;
};

#endif //GENUS_GPADDLEPROCESS_H
