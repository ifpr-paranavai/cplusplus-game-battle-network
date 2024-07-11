#include "event-manager.h"

namespace Game
{
    SDLEventManagerAdapter::SDLEventManagerAdapter()
    {
    }

    SDL_Keycode SDLEventManagerAdapter::convertKeycode(KeyCode keycode)
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
        default:
            return SDLK_UNKNOWN;
        }
    }

    bool SDLEventManagerAdapter::exitEventIsCalled()
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

    bool SDLEventManagerAdapter::isKeyPressed(KeyCode keycode)
    {
        SDL_Keycode sdlKeyCode = convertKeycode(keycode);
        SDL_Scancode sdlScancode = SDL_GetScancodeFromKey(sdlKeyCode);
        const Uint8 *currentState = SDL_GetKeyboardState(NULL);
        bool isPressed = currentState[sdlScancode] != 0;

        return isPressed;
    }

}