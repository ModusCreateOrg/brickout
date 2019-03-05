#include "GGamePlayfield.h"

GGamePlayfield::GGamePlayfield() {
#ifdef ENABLE_AUDIO
  gSoundPlayer.PlayMusic(STAGE_4_XM);
#endif
  gResourceManager.LoadBitmap(GAME_BMP, BKG_SLOT, IMAGE_ENTIRE);
//  gResourceManager.LoadBitmap(SPLASH_SPRITES_BMP, PLAYER_SLOT, IMAGE_32x32);
  mBackground = gResourceManager.GetBitmap(BKG_SLOT);
  gDisplay.SetPalette(mBackground);

}

GGamePlayfield::~GGamePlayfield() {
//  gResourceManager.ReleaseBitmapSlot(PLAYER_SLOT);
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
}

void GGamePlayfield::Render() {
  gDisplay.renderBitmap->CopyPixels(mBackground);
}

