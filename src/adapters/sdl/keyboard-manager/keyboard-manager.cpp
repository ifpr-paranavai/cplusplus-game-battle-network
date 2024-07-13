#include "keyboard-manager.h"

namespace Game
{
    SDLKeyboardManagerAdapter::SDLKeyboardManagerAdapter()
    {
    }

    SDL_Keycode SDLKeyboardManagerAdapter::convertKeycode(KeyCode keycode)
    {
        switch (keycode)
        {
        case KeyCode::ARROW_UP:
            return SDLK_UP;
        case KeyCode::ARROW_DOWN:
            return SDLK_DOWN;
        case KeyCode::ARROW_LEFT:
            return SDLK_LEFT;
        case KeyCode::ARROW_RIGHT:
            return SDLK_RIGHT;
        case KeyCode::X:
            return SDLK_x;
        default:
            return SDLK_UNKNOWN;
        }
    }

    bool SDLKeyboardManagerAdapter::exitEventIsCalled()
    {
        SDL_Event windowEvent;
        if (SDL_PollEvent(&windowEvent))
        {
            if (SDL_QUIT == windowEvent.type)
            {
                return true;
            }
        }

        return false;
    }

    bool SDLKeyboardManagerAdapter::isKeyPressed(KeyCode keycode)
    {
        SDL_Keycode sdlKeyCode = convertKeycode(keycode);
        SDL_Scancode sdlScancode = SDL_GetScancodeFromKey(sdlKeyCode);
        const Uint8 *currentState = SDL_GetKeyboardState(NULL);
        bool isPressed = currentState[sdlScancode] != 0;

        return isPressed;
    }

}