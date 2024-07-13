#include "time-manager.h"

namespace Game
{
    SDLTimeManagerAdapter::SDLTimeManagerAdapter()
    {
    }

    void SDLTimeManagerAdapter::updateTime()
    {
        LogManager::log("Updating time...");
        Uint32 currentTime = SDL_GetTicks();
        LogManager::log("currentTime get");
        this->deltaTime = (currentTime - this->lastTime) / 1000.0f;
        LogManager::log("Delta time calculated: " + std::to_string(this->deltaTime));
        lastTime = currentTime;
        LogManager::log("Time updated!");
    }

    float SDLTimeManagerAdapter::getDeltaTime()
    {
        return this->deltaTime;
    }
}