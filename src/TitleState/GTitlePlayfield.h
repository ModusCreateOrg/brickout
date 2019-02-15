#ifndef GENUS_GTITLEPLAYFIELD_H
#define GENUS_GTITLEPLAYFIELD_H

#include "Game.h"

class GTitlePlayfield : public BPlayfield {
public:
  GTitlePlayfield();
  virtual ~GTitlePlayfield();
  void Render();
public:
  BBitmap *mBackground;
};


#endif //GENUS_GTITLEPLAYFIELD_H
