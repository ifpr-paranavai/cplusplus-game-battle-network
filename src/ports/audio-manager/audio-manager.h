#pragma once
#include <string_view>
#include "../../domain/dto/music/music.h"
#include "../../domain/dto/sound-effect/sound-effect.h"

namespace Game
{
  class AudioManagerPort
  {
  public:
    virtual void playWavSoundEffect(const SoundEffect &soundEffect) = 0;
    virtual void playMusic(const Music &music) = 0;
    virtual SoundEffect initSoundEffect(std::string_view soundEffectPath) = 0;
    virtual Music initMusic(std::string_view musicPath) = 0;
    virtual void freeMusic(const Music &music) = 0;
    virtual void freeSoundEffect(const SoundEffect &soundEffect) = 0;
  };
}