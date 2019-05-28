#ifndef GENUS_GRESOURCES_H
#define GENUS_GRESOURCES_H

#include <BTypes.h>
#include "Resources.h"

enum {
  BKG_SLOT,
  PLAYER_SLOT,
  COMMON_SLOT,
  FONT_8x8_SLOT,
  FONT_16x16_SLOT
};


// BRaw slots
enum {
  SONG0_SLOT,
  SONG1_SLOT,
  SONG2_SLOT,
  SONG3_SLOT,
  SONG4_SLOT,
  SONG5_SLOT,
  SONG6_SLOT,
  SONG7_SLOT,
  SONG8_SLOT,
  SONG9_SLOT,
  SONG10_SLOT,
  SONG11_SLOT,
  SFX1_SLOT,
  SFX2_SLOT,
  SFX3_SLOT,
  SFX4_SLOT,
  SFX5_SLOT,
  SFX6_SLOT,
  SFX7_SLOT,
  SFX8_SLOT,
  SFX9_SLOT,
  SFX10_SLOT,
};


static const TInt16 MAX_BBITMAP = SPLASH_BMP + 1;

static const TUint16 IMG_DROP1 = 0;
static const TUint16 IMG_DROP2 = 4;
static const TUint16 IMG_DROP3 = 8;
static const TUint16 IMG_DROP4 = 16;
static const TUint16 IMG_DROP5 = 24;
static const TUint16 IMG_DROP6 = 32;

static const TUint8  COLOR_TEXT        = 7;
static const TUint16 COLOR_TEXT_SHADOW = 263;

static const TUint16 IMG_PADDLE = 0;
static const TUint16 IMG_BRICK_RED = 1;
static const TUint16 IMG_BRICK_GREEN = 2;
static const TUint16 IMG_BRICK_BLUE = 3;
static const TUint16 IMG_BRICK_YELLOW = 4;
static const TUint16 IMG_BALL = 8;

#endif //GENUS_GRESOURCES_H
