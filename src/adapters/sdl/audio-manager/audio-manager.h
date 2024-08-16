#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <stdexcept>
#include <string_view>
#include <unordered_map>
#include <vector>
#include "../../../ports/audio-manager/audio-manager.h"

namespace Game
{
    class SDLAudioManagerAdapter : public AudioManagerPort
    {
    private:
        Mix_Music *currentMusic = nullptr;

    public:
        SDLAudioManagerAdapter();
        void playWavSoundEffect(const SoundEffect &soundEffect) override;
        void playMusic(const Music &music) override;
        SoundEffect initSoundEffect(std::string_view soundEffectPath) override;
        Music initMusic(std::string_view musicPath) override;
    };
}