#include "GBlockProcess.h"

GBlockProcess::GBlockProcess(GGameState *aGameState, TInt aX, TInt aY, TUint16 aImage) {
  mGameState = aGameState;
  mSprite = new BSprite(0, COMMON_SLOT, aImage, STYPE_ENEMY);
  mSprite->x = aX;
  mSprite->y = aY;
  mSprite->flags |= SFLAG_RENDER | SFLAG_CHECK;
  mSprite->cMask = STYPE_PBULLET;
  mSprite->w = 16;
  mSprite->h = 8;
  aGameState->AddSprite(mSprite);
}

GBlockProcess::~GBlockProcess() {
  if (mSprite) {
    mSprite->Remove();
    delete mSprite;
  }
}

TBool GBlockProcess::RunBefore() {
  return ETrue;
}

TBool GBlockProcess::RunAfter() {
  if (mSprite->cType) {
    TBCD points(1);
    mGameState->mScore.Add(points);
    mSprite->Remove();
    delete mSprite;
    mSprite = ENull;
    return EFalse;
  }
  return ETrue;
}
