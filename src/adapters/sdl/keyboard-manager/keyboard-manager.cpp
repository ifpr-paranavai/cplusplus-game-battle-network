#include "keyboard-manager.h"
#include <SDL2/SDL.h>

namespace Game
{
    SDLKeyboardManagerAdapter::SDLKeyboardManagerAdapter()
    {
    }

    SDL_Keycode SDLKeyboardManagerAdapter::convertKeycode(KeyCode keycode)
    {
        static const std::unordered_map<KeyCode, SDL_Keycode> keycodeMap = {
            {KeyCode::ARROW_UP, SDLK_UP},
            {KeyCode::ARROW_DOWN, SDLK_DOWN},
            {KeyCode::ARROW_LEFT, SDLK_LEFT},
            {KeyCode::ARROW_RIGHT, SDLK_RIGHT},
            {KeyCode::X, SDLK_x},
            {KeyCode::C, SDLK_c},
        };

        auto it = keycodeMap.find(keycode);
        if (it != keycodeMap.end())
        {
            return it->second;
        }
        return SDLK_UNKNOWN;
    }

    bool SDLKeyboardManagerAdapter::exitEventIsCalled()
    {
        SDL_Event windowEvent;
        while (SDL_PollEvent(&windowEvent)) // Use um loop para processar todos os eventos pendentes
        {
            if (windowEvent.type == SDL_QUIT)
            {
                return true;
            }
        }
        return false;
    }

    bool SDLKeyboardManagerAdapter::isKeyPressed(KeyCode keycode)
    {
        const SDL_Keycode sdlKeyCode = convertKeycode(keycode);
        if (sdlKeyCode == SDLK_UNKNOWN)
        {
            return false;
        }

        const SDL_Scancode sdlScancode = SDL_GetScancodeFromKey(sdlKeyCode);
        const Uint8 *currentState = SDL_GetKeyboardState(NULL);
        const bool isPressed = currentState[sdlScancode] != 0;

        if (isPressed && keyStates[sdlKeyCode] == false)
        {
            keyStates[sdlKeyCode] = true;
            return true;
        }
        else if (!isPressed && keyStates[sdlKeyCode] == true)
        {
            keyStates[sdlKeyCode] = false;
            return false;
        }
        else
        {
            return false;
        }
    }
}
