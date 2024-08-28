#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <cstring>
#include <unordered_map>
#include "../../../ports/keyboard-manager/keyboard-manager.h"

namespace Game
{
    class SDLKeyboardManagerAdapter : public KeyboardManagerPort
    {
    private:
        std::unordered_map<SDL_Keycode, bool> keyStates;

        SDL_Keycode convertKeycode(KeyCode keyCode);

    public:
        SDLKeyboardManagerAdapter();

        bool exitEventIsCalled() override;
        bool isKeyPressed(KeyCode keyCode) override;
    };
}