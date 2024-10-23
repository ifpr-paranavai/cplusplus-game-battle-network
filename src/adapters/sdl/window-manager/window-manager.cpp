#include "window-manager.h"

namespace Game
{
  void SDLWindowManagerAdapter::createWindow(int width, int height)
  {
    this->window = nullptr;
    SDL_Init(SDL_INIT_EVERYTHING);
    this->window =
        SDL_CreateWindow("Battle Network", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (this->window == NULL)
    {
      throw std::runtime_error("SDL_CreateWindow Error: " + std::string(SDL_GetError()));
    }
  }

  void SDLWindowManagerAdapter::destroyWindow()
  {
    this->window = nullptr;
    SDL_DestroyWindow(this->window);
    SDL_Quit();
  }

  SDL_Window *SDLWindowManagerAdapter::getWindow()
  {
    return this->window;
  }
} // namespace Game