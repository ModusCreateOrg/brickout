#include "GBallProcess.h"
#include <math.h>

#define PI TFloat(M_PI)

class BallSprite : public BSprite {
public:
  BallSprite(TInt aPri, TUint16 bm, TUint16 img = 0,
                             TUint32 aType = STYPE_DEFAULT) : BSprite(aPri, bm, img, aType){
  }
  void Collide(BSprite *aOther) {
    if (aOther->type == STYPE_PLAYER) {
      if (y < aOther->y+vy ) {
        vx = (x - aOther->x -16)/4;
        y = aOther->y - 4;
        cType |= aOther->type;
      }
    }
    else if (aOther->type == STYPE_ENEMY) {
      // collide with block
      cType |= aOther->type;
      if (vy < 0) {
        y = aOther->y + aOther->h - vy;
      }
      else {
        y = aOther->y + vy;
      }
    }
    else {
      cType |= aOther->type;
    }
  };
};

GBallProcess::GBallProcess(GGameState *aGameState, TFloat aVelocity) {
  this->mGameState = aGameState;
  this->mVelocity = aVelocity;
  mSprite = new BallSprite(0, COMMON_SLOT, IMG_BALL, STYPE_PBULLET|STYPE_EBULLET);
  mSprite->cMask = STYPE_ENEMY | STYPE_PLAYER;
  mSprite->flags |= SFLAG_RENDER | SFLAG_CHECK;
  mSprite->w = mSprite->h = 4;
  aGameState->AddSprite(mSprite);
  Reset(this->mVelocity);
}

GBallProcess::~GBallProcess() {
  mSprite->Remove();
  delete mSprite;
}

// velocity determines difficulty (speed of ball)
void GBallProcess::Reset(TFloat aVelocity) {
  mSprite->x = TFloat(SCREEN_WIDTH) / 2;
  mSprite->y = TFloat(SCREEN_HEIGHT) / 2;

  TFloat angle = Random(45, 135) * PI / 180;

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
  return ETrue;
}

TBool GBallProcess::RunAfter() {
  if (mSprite->cType & STYPE_PLAYER) {
    mSprite->vy = -mSprite->vy;
    mSprite->cType &= ~STYPE_PLAYER;
  }
  else if (mSprite->cType & STYPE_ENEMY) {
    mSprite->vy = -mSprite->vy;
    mSprite->cType &= ~STYPE_ENEMY;
  }
  if (mSprite->y > SCREEN_HEIGHT) {
    mGameState->Death();
    return EFalse;
  }
  return ETrue;
}
