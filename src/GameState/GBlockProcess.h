#ifndef GENUS_GBLOCKPROCESS_H
#define GENUS_GBLOCKPROCESS_H

#include "Game.h"

class GBlockProcess : public BProcess {
public:
  GBlockProcess(GGameState *aGameState, TInt aX, TInt aY, TUint16 aImage);
  virtual ~GBlockProcess();
public:
  TBool RunBefore();
  TBool RunAfter();
protected:
  BSprite *mSprite;
  GGameState *mGameState;
};

#endif //GENUS_GBLOCKPROCESS_H
