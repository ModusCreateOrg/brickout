#ifndef GENUS_GGAMEPLAYFIELD_H
#define GENUS_GGAMEPLAYFIELD_H

#include "Game.h"

class GGamePlayfield : public BPlayfield {
public:
  GGamePlayfield();

  virtual ~GGamePlayfield();

  void Render();

public:
  BBitmap *mBackground;
};


#endif //GENUS_GGAMEPLAYFIELD_H
