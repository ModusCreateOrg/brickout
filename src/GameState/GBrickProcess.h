#ifndef GBRICK_PROCESS_H
#define GBRICK_PROCESS_H

#include "Game.h"

class BrickSprite;

class GBrickProcess : public BProcess {
public:
  GBrickProcess(GGameState *aGameState, TInt aX, TInt aY, TUint16 aImage);
  virtual ~GBrickProcess();
public:
  TBool RunBefore();
  TBool RunAfter();
protected:
  BSprite *mSprite;
  GGameState *mGameState;
};

#endif //GBRICK_PROCESS_H
