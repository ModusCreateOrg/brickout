//
// Created by Jesus Garcia on 10/2/18.
//

#include "Game.h"
#include "GSoundPlayer.h"
#include "GResources.h"
#include "Memory.h"

#define DISABLE_AUDIO
//#undef DISABLE_AUDIO


GSoundPlayer gSoundPlayer;

#define MUSIC_VOLUME (.15)
#define SFX_VOLUME (.25)

void GSoundPlayer::Init(TUint8 aNumberFxChannels, TUint8 aNumberFxSlots) {
  BSoundPlayer::Init(aNumberFxChannels, aNumberFxSlots);

  mMaxSongs = 8;
  mSongSlots = (SongSlot *)AllocMem(sizeof(SongSlot) * mMaxSongs, MEMF_SLOW);

  const TUint16 allSongs[] = {
    EMPTYSONG_XM,
    INTRO_XM,
    STAGE_1_XM,
    STAGE_2_XM,
    STAGE_3_XM,
    STAGE_4_XM,
    STAGE_5_XM,
    GAMEOVER_XM,
  };

  for (TUint8 i = 0; i < mMaxSongs; i++) {
    auto *slot = (SongSlot *)AllocMem(sizeof(SongSlot), MEMF_SLOW);

    slot->mResourceNumber = allSongs[i];
    slot->mSlotNumber = SONG0_SLOT + i;

    gResourceManager.LoadRaw(allSongs[i], slot->mSlotNumber);
    slot->mRaw = gResourceManager.GetRaw(slot->mSlotNumber);

    mSongSlots[i] = *slot;
    FreeMem(slot);
  }


  PlayMusic(EMPTYSONG_XM);
  SetMusicVolume(MUSIC_VOLUME);
  SetEffectsVolume(SFX_VOLUME);
  MuteMusic(false);
}

TBool GSoundPlayer::PlayMusic(TInt16 aResourceId) {
  TBool music = BSoundPlayer::PlayMusic(aResourceId);
//  printf("%s %i\n", __PRETTY_FUNCTION__, aResourceId);
  // BSoundPlayer::PlayMusic un-mutes the music
  // We have to re-mute it in case of mute == true
  MuteMusic(false);

  return music;
}

TBool GSoundPlayer::LoadSongSlot(TInt16 aResourceId) {

  for (TUint8 i = 0; i < mMaxSongs; i++) {
    if (mSongSlots[i].mResourceNumber == aResourceId) {
      return LoadSong(mSongSlots[i].mRaw);
    }
  }

  printf("WARNING :: Could not find song %i\n", aResourceId);

  return false;
}


TBool GSoundPlayer::LoadEffects() {
  // Load effects
  const TUint16 mEffectsList[] = {
    SFX_BOUNCE_OFF_PLAYER_WAV,
    SFX_BOUNCE_WALL_WAV,
    SFX_KILL_BLOCK_WAV,
    SFX_START_GAME_WAV,
    SFX_NEW_BALL_WAV,
  };

  for (TUint8 i = 0; i < 5; i++) {
    LoadEffect(mEffectsList[i], i);
  }

  SetMusicVolume(MUSIC_VOLUME);
  SetEffectsVolume(SFX_VOLUME);
  return ETrue;
}


BRaw *GSoundPlayer::LoadEffectResource(TUint16 aResourceId, TInt16 aSlotNumber) {
  gResourceManager.LoadRaw(aResourceId, SFX1_SLOT + aSlotNumber);
  return gResourceManager.GetRaw(SFX1_SLOT + aSlotNumber);
}


void GSoundPlayer::SfxBounceOffPlayer() {
  gSoundPlayer.PlaySfx(/*SFX_BOUNCE_OFF_PLAYER_WAV*/0);
}


void GSoundPlayer::SfxBounceWall() {
  printf("SfxBounceWall\n");
  gSoundPlayer.PlaySfx(/*SFX_BOUNCE_WALL*/1);
}

void GSoundPlayer::SfxKillBlock() {
  gSoundPlayer.PlaySfx(/*SFX_KILL_BLOCK*/2);
}


void GSoundPlayer::SfxStartGame() {
  gSoundPlayer.PlaySfx(/*SFX_START_GAME_WAV*/3);
}

void GSoundPlayer::SfxNewBall() {
  gSoundPlayer.PlaySfx(/*SFX_NEW_BALL_WAV*/4);
}