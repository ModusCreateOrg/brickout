#ifndef GENUS_GGAMESTATE_H
#define GENUS_GGAMESTATE_H

#include "Game.h"

class GGameState : public BGameEngine {
public:
  GGameState();
  ~GGameState();
  void PostRender();
private:
  BFont *mFont8, *mFont16;
public:
  TBCD mScore;
};


#endif //GENUS_GGAMESTATE_H
