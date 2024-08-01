#include "keyboard-manager.h"
#include <SDL2/SDL.h>

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
            return SDLK_x; // Certifique-se de usar o SDL_Keycode correto para "X"
        default:
            return SDLK_UNKNOWN;
        }
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
        SDL_Keycode sdlKeyCode = convertKeycode(keycode);
        SDL_Scancode sdlScancode = SDL_GetScancodeFromKey(sdlKeyCode);
        const Uint8 *currentState = SDL_GetKeyboardState(NULL);
        return currentState[sdlScancode] != 0;
    }
}
