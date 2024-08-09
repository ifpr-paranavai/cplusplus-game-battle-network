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

    void SDLAudioManagerAdapter::playWavSoundEffect(const SoundEffect &soundEffect)
    {
        Mix_Chunk *sound = std::any_cast<Mix_Chunk *>(soundEffect.data);

        if (Mix_PlayChannel(-1, sound, 0) == -1)
        {
            Mix_FreeChunk(sound);
            throw std::runtime_error("Failed to play sound: " + std::string(Mix_GetError()));
        }
    }

    void SDLAudioManagerAdapter::playMusic(const Music &music)
    {
        if (this->currentMusic != nullptr)
        {
            Mix_FreeMusic(this->currentMusic);
        }

        this->currentMusic = std::any_cast<Mix_Music *>(music.data);

        if (Mix_PlayMusic(this->currentMusic, -1) == -1)
        {
            throw std::runtime_error("Failed to play music: " + std::string(Mix_GetError()));
        }
    }

    SoundEffect SDLAudioManagerAdapter::initSoundEffect(std::string_view soundEffectPath)
    {
        Mix_Chunk *sound = Mix_LoadWAV(soundEffectPath.data());
        if (sound == nullptr)
        {
            throw std::runtime_error("Failed to load sound: " + std::string(Mix_GetError()));
        }

        return SoundEffect{std::make_any<Mix_Chunk *>(sound)};
    }

    Music SDLAudioManagerAdapter::initMusic(std::string_view musicPath)
    {
        Mix_Music *music = Mix_LoadMUS(musicPath.data());
        if (music == nullptr)
        {
            throw std::runtime_error("Failed to load music: " + std::string(Mix_GetError()));
        }

        return Music{std::make_any<Mix_Music *>(music)};
    }

}