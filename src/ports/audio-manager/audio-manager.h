#pragma once
#include <string_view>

namespace Game
{
    class AudioManagerPort
    {
    public:
        virtual void playWavSoundEffect(std::string_view path) = 0;
        virtual void playMp3Music(std::string_view path) = 0;
    };
}