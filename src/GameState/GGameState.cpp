#include "Game.h"

#include "GGamePlayfield.h"
#include "GPaddleProcess.h"
#include "GBallProcess.h"
#include "GBrickProcess.h"

const TInt LEVEL_X = 8;
const TInt LEVEL_Y = 2;

const TInt SCORE_X = 120;
const TInt SCORE_Y = 2;

const TInt LIVES_X = 320-32;
const TInt LIVES_Y = 2;

GGameState::GGameState() : BGameEngine(gViewPort) {
  mPlayfield = new GGamePlayfield();
  mFont8     = new BFont(gResourceManager.GetBitmap(FONT_8x8_SLOT), FONT_16x16);
  mFont16    = new BFont(gResourceManager.GetBitmap(FONT_16x16_SLOT), FONT_16x16);
  gResourceManager.LoadBitmap(GAME_SPRITES_BMP, COMMON_SLOT, IMAGE_16x16);
  gResourceManager.LoadBitmap(PLAYER_SPRITES_BMP, PLAYER_SLOT, IMAGE_32x32);
  BBitmap *b = gResourceManager.GetBitmap(PLAYER_SLOT);
  printf("transparent = %d\n", b->TransparentColor());
  AddProcess(this->mPaddleProcess = new GPaddleProcess(this));
  AddProcess(mBallProcess = new GBallProcess(this));
  mScore.mValue = 0;
  mLevel.mValue = 1;
  mLives.mValue = 3;
  Reset();
}

GGameState::~GGameState() {
  gResourceManager.ReleaseBitmapSlot(PLAYER_SLOT);
  gResourceManager.ReleaseBitmapSlot(COMMON_SLOT);
  delete mFont16;
  delete mFont8;
}

void GGameState::Reset() {
  if (mBallProcess) {
    mBallProcess->Reset();
  }
  GBrickProcess::mBrickCount = 0;
  for (TUint16 row = 0; row < 11; row++) {
    for (TUint16 col = 0; col < 20; col++) {
      AddProcess(new GBrickProcess(this, col * 16, 24 + row * 8, TUint16((row % 5) + 0)));
    }
  }
}

void GGameState::PostRender() {
  BBitmap *bm = gDisplay.renderBitmap;
  char    text[12];

  for (TInt i   = 0; i < 8; i++) {
    TInt v = (mLevel.mValue >> ((7 - i) * 4)) & 0x0f;
    text[i] = '0' + char(v);
    if (text[i] == '0') {
      text[i] = ' ';
    }
  }
  text[8] = '\0';
  text[5] = 'L';
  bm->DrawStringShadow(ENull, &text[5], mFont16, LEVEL_X, LEVEL_Y, COLOR_TEXT, COLOR_TEXT_SHADOW, -1, -6);

  for (TInt i   = 0; i < 8; i++) {
    TInt v = (mScore.mValue >> ((7 - i) * 4)) & 0x0f;
    text[i] = '0' + char(v);
  }
  text[8] = '\0';
  bm->DrawStringShadow(ENull, text, mFont16, SCORE_X, SCORE_Y, COLOR_TEXT, COLOR_TEXT_SHADOW, -1, -6);

  for (TInt i   = 0; i < 8; i++) {
    TInt v = (mLives.mValue >> ((7 - i) * 4)) & 0x0f;
    text[i] = '0' + char(v);
  }
  text[8] = '\0';
  bm->DrawStringShadow(ENull, &text[7], mFont16, LIVES_X, LIVES_Y, COLOR_TEXT, COLOR_TEXT_SHADOW, -1, -6);

  if (mLives.mValue <= 0) {
    bm->DrawStringShadow(ENull, "GAME OVER", mFont16, (320-9*16)/2, 120-8, COLOR_TEXT, COLOR_TEXT_SHADOW);
    if (gControls.WasPressed(BUTTON_ANY)) {
      gGame->SetState(GAME_STATE_TITLE);
    }
  }
}

void GGameState::Death() {
  if (mLives.mValue) {
    mLives.mValue --;
  }
  if (mLives.mValue > 0) {
    mPaddleProcess->Reset();
    AddProcess(mBallProcess = new GBallProcess(this));
  }
}
