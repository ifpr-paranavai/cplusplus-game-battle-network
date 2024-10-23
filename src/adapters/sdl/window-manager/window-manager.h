#pragma once
#include "../../../ports/window-manager/window-manager.h"
#include <SDL2/SDL.h>
#include <iostream>

namespace Game
{
  class SDLWindowManagerAdapter : public WindowManagerPort
  {
  private:
    SDL_Window *window = nullptr;
    int width = 0;
    int height = 0;

  public:
    ~SDLWindowManagerAdapter()
    {
      this->destroyWindow();
    }

    void createWindow(int width, int height) override;
    void destroyWindow() override;
    SDL_Window *getWindow();

    int getWidth() const
    {
      return this->width;
    }

    int getHeight() const
    {
      return this->height;
    }
  };
}