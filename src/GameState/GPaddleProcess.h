#ifndef GENUS_GPADDLEPROCESS_H
#define GENUS_GPADDLEPROCESS_H

#include "Game.h"

class GPaddleProcess : public BProcess {
public:
  GPaddleProcess(BGameEngine *aGameEngine);
  ~GPaddleProcess();
public:
  void Reset();
public:
  TBool RunBefore();
  TBool RunAfter();
protected:
  BSprite *mSprite;
};

#endif //GENUS_GPADDLEPROCESS_H
