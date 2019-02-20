#include "GBallProcess.h"
#include <math.h>

GBallProcess::GBallProcess(BGameEngine *aGameEngine, TFloat aVelocity) {
  this->mVelocity = aVelocity;
  mSprite = new BSprite(0, COMMON_SLOT, IMG_BALL, STYPE_PBULLET|STYPE_EBULLET);
  mSprite->cMask = STYPE_ENEMY;
  mSprite->flags |= SFLAG_RENDER | SFLAG_CHECK;
  mSprite->w = mSprite->h = 4;
  aGameEngine->AddSprite(mSprite);
  Reset(this->mVelocity);
}

GBallProcess::~GBallProcess() {
  mSprite->Remove();
  delete mSprite;
}

// velocity determines difficulty (speed of ball)
void GBallProcess::Reset(TFloat aVelocity) {
  mSprite->x = TFloat(SCREEN_WIDTH) / 2 - Random(0, SCREEN_WIDTH / 4);
  mSprite->y = TFloat(SCREEN_HEIGHT) / 2 + Random(0, SCREEN_HEIGHT / 4);

  TFloat angle = TFloat(Random(45, 135)) * M_PI / 180;

  mSprite->vx = cos(angle) * aVelocity;
  mSprite->vy = sin(angle) * aVelocity;
  mSprite->flags |= SFLAG_RENDER;
}

TBool GBallProcess::RunBefore() {
  const TFloat newX = mSprite->x + mSprite->vx,
               newY = mSprite->y + mSprite->vy;
  if (newX < 0) {
    mSprite->x = 0;
    mSprite->vx = -mSprite->vx;
  }
  if (newX > (SCREEN_WIDTH - 4)) {
    mSprite->x = (SCREEN_WIDTH - 4);
    mSprite->vx = -mSprite->vx;
  }
  if (newY < 0) {
    mSprite->y = 0;
    mSprite->vy = -mSprite->vy;
  }
  if (newY > (SCREEN_HEIGHT - 4)) {
    mSprite->y = (SCREEN_HEIGHT - 4);
    mSprite->vy = -mSprite->vy;
  }
  return ETrue;
}

TBool GBallProcess::RunAfter() {
  if (mSprite->cType) {
    mSprite->vy = -mSprite->vy;
    mSprite->cType = 0;
  }
  return ETrue;
}
