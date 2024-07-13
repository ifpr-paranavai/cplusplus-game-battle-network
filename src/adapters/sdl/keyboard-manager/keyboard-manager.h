#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <cstring>
#include "../../../ports/keyboard-manager/keyboard-manager.h"

namespace Game
{
    class SDLKeyboardManagerAdapter : public KeyboardManagerPort
    {
    private:
        SDL_Keycode convertKeycode(KeyCode keyCode);

    public:
        SDLKeyboardManagerAdapter();

        bool exitEventIsCalled() override;
        bool isKeyPressed(KeyCode keyCode) override;
    };
}