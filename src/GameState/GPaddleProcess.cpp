#include "GPaddleProcess.h"

static const TInt DELTA_X = 4;

GPaddleProcess::GPaddleProcess(BGameEngine *aGameEngine) {
  mSprite = new BSprite(0, PLAYER_SLOT, IMG_PADDLE);
  mSprite->x = 160-16;
  mSprite->y = 220;
  mSprite->w = 32;
  mSprite->h = 8;
  mSprite->flags |= SFLAG_RENDER;
  aGameEngine->AddSprite(mSprite);
}

GPaddleProcess::~GPaddleProcess() {
  mSprite->Remove();
  delete mSprite;
}

TBool GPaddleProcess::RunBefore() {
  return ETrue;
}
TBool GPaddleProcess::RunAfter() {
  if (gControls.IsPressed(JOYLEFT)) {
    mSprite->x = mSprite->x - DELTA_X;
    if (mSprite->x < 0) {
      mSprite->x = 0;
    }
  }
  else if (gControls.IsPressed(JOYRIGHT)) {
    mSprite->x = mSprite->x + DELTA_X;
    if (mSprite->x > (320-32) ) {
      mSprite->x = 320-32;
    }
  }
  return ETrue;
}
// void BBitmap::FillRect(BViewPort *aViewPort, TInt aX1, TInt aY1, TInt aX2, TInt aY2, TUint8 aColor) {
