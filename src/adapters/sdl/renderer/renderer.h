#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <SDL2/SDL_ttf.h>
#include "../../../utils/global/global.h"
#include "../../../ports/renderer/renderer.h"
#include "../window-manager/window-manager.h"

namespace Game
{
    class SDLRendererAdapter : public RendererPort
    {
    private:
        SDL_Renderer *sdlRenderer;
        TTF_Font *font;

        SDL_Renderer *getRenderer();

        unsigned int getHexColorValue(std::string_view hexColor);

    public:
        SDLRendererAdapter();
        int getTextHeight(std::string_view text) override;
        int getTextWidth(std::string_view text) override;
        void renderElement(const RenderDataDTO &renderDataDTO) override;
        void updateScreen() override;
        void renderText(std::string_view text, Vector position) override;
        void destroyRenderer() override;
    };
}
