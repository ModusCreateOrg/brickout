#include "Game.h"

#include "GGamePlayfield.h"
#include "GPaddleProcess.h"
#include "GBallProcess.h"
#include "GBlockProcess.h"

const TInt SCORE_X = 120;
const TInt SCORE_Y = 2;

GGameState::GGameState() : BGameEngine(gViewPort) {
  mPlayfield = new GGamePlayfield();
  mFont8     = new BFont(gResourceManager.GetBitmap(FONT_8x8_SLOT), FONT_16x16);
  mFont16    = new BFont(gResourceManager.GetBitmap(FONT_16x16_SLOT), FONT_16x16);
  gResourceManager.LoadBitmap(GAME_SPRITES_BMP, COMMON_SLOT, IMAGE_16x16);
  gResourceManager.LoadBitmap(PLAYER_SPRITES_BMP, PLAYER_SLOT, IMAGE_32x32);
  BBitmap *b = gResourceManager.GetBitmap(PLAYER_SLOT);
  printf("transparent = %d\n", b->TransparentColor());
  AddProcess(new GPaddleProcess(this));
  AddProcess(new GBallProcess(this));
  for (TUint16 row = 0; row < 11; row++) {
    for (TUint16 col = 0; col < 20; col++) {
      AddProcess(new GBlockProcess(this, col * 16, 24 + row * 8, TUint16((row % 5) + 0)));
    }
  }
}

GGameState::~GGameState() {
  gResourceManager.ReleaseBitmapSlot(PLAYER_SLOT);
  gResourceManager.ReleaseBitmapSlot(COMMON_SLOT);
  delete mFont16;
  delete mFont8;
  // delete mPlayfield;
}

void GGameState::PostRender() {
  BBitmap *bm = gDisplay.renderBitmap;
  char    score_text[12];

  for (TInt i   = 0; i < 8; i++) {
    TInt v = (mScore.mValue >> ((7 - i) * 4)) & 0x0f;
    score_text[i] = '0' + char(v);
  }
  score_text[8] = '\0';
  bm->DrawStringShadow(ENull, score_text, mFont16, SCORE_X, SCORE_Y, COLOR_TEXT, COLOR_TEXT_SHADOW, -1, -6);
}

