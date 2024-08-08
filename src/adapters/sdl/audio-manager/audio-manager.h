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
        std::unordered_map<std::string, Mix_Chunk *> soundCache;
        Mix_Music *currentMusic;

    public:
        SDLAudioManagerAdapter();
        virtual void playWavSoundEffect(std::string_view path) override;
        virtual void playMp3Music(std::string_view path) override;
    };
}