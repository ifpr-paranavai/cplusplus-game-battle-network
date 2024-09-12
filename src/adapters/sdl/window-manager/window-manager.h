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

    public:
        ~SDLWindowManagerAdapter()
        {
            this->destroyWindow();
        }

        void createWindow(int width, int height) override;
        void destroyWindow() override;
        SDL_Window *getWindow();
    };
}