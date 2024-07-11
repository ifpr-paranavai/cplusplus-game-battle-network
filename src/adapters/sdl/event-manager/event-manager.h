#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <cstring>
#include "../../../ports/event-manager/event-manager.h"

namespace Game
{
    class SDLEventManagerAdapter : public EventManagerPort
    {
    private:
        SDL_Keycode convertKeycode(KeyCode keyCode);

    public:
        SDLEventManagerAdapter();

        bool exitEventIsCalled() override;
        bool isKeyPressed(KeyCode keyCode) override;
    };
}