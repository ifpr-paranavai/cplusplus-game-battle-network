#include "window-manager.h"

namespace Game
{
    void SDLWindowManagerAdapter::createWindow(int width, int height)
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        this->window = SDL_CreateWindow(
            "Battle Network", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
        if (this->window == NULL)
        {
            throw std::runtime_error("SDL_CreateWindow Error: " + std::string(SDL_GetError()));
        }
    }

    void SDLWindowManagerAdapter::destroyWindow()
    {
        SDL_DestroyWindow(this->window);
        SDL_Quit();
    }

    SDL_Window *SDLWindowManagerAdapter::getWindow()
    {
        return this->window;
    }
}