#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <SDL2/SDL_ttf.h>
#include "../../../ports/renderer/renderer.h"
#include "../window-manager/window-manager.h"

namespace Game
{
    class SDLRendererAdapter : public RendererPort
    {
    private:
        SDLWindowManagerAdapter *sdlWindowManagerAdapter;
        SDL_Renderer *sdlRenderer;
        TTF_Font *font;

        SDL_Renderer *getRenderer();

        unsigned int getHexColorValue(std::string_view hexColor);

    public:
        SDLRendererAdapter(SDLWindowManagerAdapter *_sdlWindowManagerAdapter);
        void renderElement(const RenderDataDTO &renderDataDTO) override;
        void updateScreen() override;
        void renderText(std::string_view text, int x, int y) override;
    };
}
