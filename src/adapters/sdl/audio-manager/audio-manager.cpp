#include "audio-manager.h"

namespace Game
{
    SDLAudioManagerAdapter::SDLAudioManagerAdapter()
    {
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            throw std::runtime_error("SDL_mixer could not initialize! SDL_mixer Error: " + std::string(Mix_GetError()));
        }
    }

    void SDLAudioManagerAdapter::playWavSoundEffect(std::string_view path)
    {
        Mix_Chunk *sound = nullptr;

        auto it = soundCache.find(path.data());
        if (it != soundCache.end())
        {
            sound = it->second;
        }
        else
        {
            sound = Mix_LoadWAV(path.data());
            if (sound == nullptr)
            {
                throw std::runtime_error("Failed to load sound: " + std::string(Mix_GetError()));
            }
            soundCache[path.data()] = sound;
        }

        if (Mix_PlayChannel(-1, sound, 0) == -1)
        {
            Mix_FreeChunk(sound);
            throw std::runtime_error("Failed to play sound: " + std::string(Mix_GetError()));
        }
    }

    void SDLAudioManagerAdapter::playMp3Music(std::string_view path)
    {
        Mix_Music *newMusic = Mix_LoadMUS(path.data());
        if (newMusic == nullptr)
        {
            throw std::runtime_error("Failed to load music: " + std::string(Mix_GetError()));
        }

        // Se houver música atual, pare-a antes de carregar a nova
        if (this->currentMusic != nullptr)
        {
            Mix_FreeMusic(this->currentMusic);
        }

        this->currentMusic = newMusic;

        // Tocar a música em loop (-1 significa loop infinito)
        if (Mix_PlayMusic(this->currentMusic, -1) == -1)
        {
            throw std::runtime_error("Failed to play music: " + std::string(Mix_GetError()));
        }
    }

}