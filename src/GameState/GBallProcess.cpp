#include "GBallProcess.h"
#include <math.h>

GBallProcess::GBallProcess(BGameEngine *aGameEngine) {
  mSprite = new BSprite(0, PLAYER_SLOT, IMG_BALL);
  aGameEngine->AddSprite(mSprite);
  Reset();
}

GBallProcess::~GBallProcess() {
  mSprite->Remove();
  delete mSprite;
}

// velocity determines difficulty (speed of ball)
void GBallProcess::Reset(TFloat aVelocity) {
  mSprite->x = TFloat(SCREEN_WIDTH) / 2 - Random(0, SCREEN_WIDTH / 4);
  mSprite->y = TFloat(SCREEN_HEIGHT) / 2 - Random(0, SCREEN_HEIGHT / 4);

  TFloat angle = TFloat(Random(0, 180)) * M_PI / 180;

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
  return ETrue;
}
