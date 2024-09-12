#include "time-manager.h"

namespace Game
{
    void SDLTimeManagerAdapter::updateTime()
    {
        Uint32 currentTime = SDL_GetTicks();
        this->deltaTime = (currentTime - this->lastTime) / 1000.0f;
        lastTime = currentTime;
    }

}