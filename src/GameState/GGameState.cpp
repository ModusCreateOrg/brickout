#include "Game.h"

#include "GGamePlayfield.h"
#include "GPaddleProcess.h"
#include "GBallProcess.h"

const TInt SCORE_X = 120;
const TInt SCORE_Y = 2;

GGameState::GGameState() : BGameEngine(gViewPort) {
  mPlayfield = new GGamePlayfield();
  mFont8     = new BFont(gResourceManager.GetBitmap(FONT_8x8_SLOT), FONT_16x16);
  mFont16    = new BFont(gResourceManager.GetBitmap(FONT_16x16_SLOT), FONT_16x16);
  gResourceManager.LoadBitmap(GAME_SPRITES_BMP, PLAYER_SLOT, IMAGE_16x16);
  BBitmap *b = gResourceManager.GetBitmap(PLAYER_SLOT);
  printf("transparent = %d\n", b->TransparentColor());
  AddProcess(new GPaddleProcess(this));
  AddProcess(new GBallProcess(this));
}

GGameState::~GGameState() {
  gResourceManager.ReleaseBitmapSlot(PLAYER_SLOT);
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

