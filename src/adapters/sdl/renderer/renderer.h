#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../../ports/renderer/renderer.h"
#include "../window-manager/window-manager.h"

namespace Game
{
    class SDLRendererAdapter : public RendererPort
    {
    private:
        std::unordered_map<std::string, SDL_Texture *> textureCache;
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
        void renderSprite(const std::string &path, float x, float y, float width, float height, bool flipHorizontal = false) override;
    };
}
