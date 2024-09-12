#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "../../../ports/time-manager/time-manager.h"
#include "../../../utils/log-manager/log-manager.h"

namespace Game
{
    class SDLTimeManagerAdapter : public TimeManagerPort
    {
    private:
        Uint32 lastTime = 0;
        float deltaTime;

    public:
        void updateTime() override;

        float getDeltaTime() override
        {
            return this->deltaTime;
        }
    };
}