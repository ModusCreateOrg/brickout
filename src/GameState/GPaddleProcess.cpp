#include "GPaddleProcess.h"

static const TInt DELTA_X = 4;

GPaddleProcess::GPaddleProcess(GGameState *aGameState) {
  mGameState = aGameState;
  mSprite = new BSprite(0, PLAYER_SLOT, IMG_PADDLE, STYPE_PLAYER);
  mSprite->w = 32;
  mSprite->h = 9;
  mSprite->flags |= SFLAG_RENDER | SFLAG_CHECK;
  mSprite->cMask |= STYPE_EBULLET;
  Reset();
  mGameState->AddSprite(mSprite);
}

GPaddleProcess::~GPaddleProcess() {
  mSprite->Remove();
  delete mSprite;
}

void GPaddleProcess::Reset() {
  mSprite->x = 160-16;
  mSprite->y = 220;
}
TBool GPaddleProcess::RunBefore() {
  return ETrue;
}
TBool GPaddleProcess::RunAfter() {
  if (mGameState->mLives.mValue > 0) {
    if (mSprite->cType) {
      mSprite->cType = 0;
    }
    if (gControls.IsPressed(JOYLEFT)) {
      mSprite->x = mSprite->x - DELTA_X;
      if (mSprite->x < 0) {
        mSprite->x = 0;
      }
    } else if (gControls.IsPressed(JOYRIGHT)) {
      mSprite->x = mSprite->x + DELTA_X;
      if (mSprite->x > (320 - 32)) {
        mSprite->x = 320 - 32;
      }
    }
  }
  return ETrue;
}
// void BBitmap::FillRect(BViewPort *aViewPort, TInt aX1, TInt aY1, TInt aX2, TInt aY2, TUint8 aColor) {
