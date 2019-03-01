#include "GBrickProcess.h"

TInt GBrickProcess::mBrickCount = 0;

GBrickProcess::GBrickProcess(GGameState *aGameState, TInt aX, TInt aY, TUint16 aImage) {
  mGameState = aGameState;
  mSprite = new BSprite(0, COMMON_SLOT, aImage, STYPE_ENEMY);
  mSprite->x = aX;
  mSprite->y = aY;
  mSprite->flags |= SFLAG_RENDER | SFLAG_CHECK;
  mSprite->cMask = STYPE_PBULLET;
  mSprite->w = 16;
  mSprite->h = 8;
  aGameState->AddSprite(mSprite);
  mBrickCount++;
}

GBrickProcess::~GBrickProcess() {
  if (mSprite) {
    mSprite->Remove();
    delete mSprite;
  }
}

TBool GBrickProcess::RunBefore() {
  return ETrue;
}

TBool GBrickProcess::RunAfter() {
  if (mSprite->cType) {
    TBCD points(1);
    mGameState->mScore.Add(points);
    mSprite->Remove();
    delete mSprite;
    mSprite = ENull;
    mBrickCount--;
    if (mBrickCount <= 0) {
      TBCD one(1);
      mGameState->mLevel.Add(one);
      mGameState->Reset();
    }
    return EFalse;
  }
  return ETrue;
}
