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
    const int defaultFontSize = 26;
    SDL_Renderer *sdlRenderer = nullptr;
    TTF_Font *font = nullptr;

    SDL_Renderer *getRenderer();

  public:
    SDLRendererAdapter();
    ~SDLRendererAdapter();
    int getTextHeight(std::string_view text) override;
    int getTextWidth(std::string_view text) override;
    void renderElement(const RenderElementData &renderDataDTO) override;
    void renderBorder(const RenderElementData &renderDataDTO) override;
    void updateScreen() override;
    void renderText(const RenderTextData &renderTextData) override;
    void destroyRenderer() override;
    void renderSprite(const SpriteTexture &spriteTexture, Vector position) override;
    SpriteTexture getSpriteTexture(const RenderSpriteData &renderSpriteData) override;
    void destroySpriteTexture(const SpriteTexture &spriteTexture) override;
  };
}
