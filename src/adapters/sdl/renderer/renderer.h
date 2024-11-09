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
    SDL_Renderer *sdlRenderer = nullptr;

  public:
    SDLRendererAdapter();
    ~SDLRendererAdapter();
    SDL_Renderer *getRenderer();
    void renderElement(const RenderElementData &renderDataDTO) override;
    void renderBorder(const RenderElementData &renderDataDTO) override;
    void updateScreen() override;
    void destroyRenderer() override;
    void renderSprite(const RenderSpriteData &renderSpriteData) override;
    SpriteTexture getSpriteTexture(const CreateSpriteTextureData &renderSpriteData) override;
    void destroySpriteTexture(const SpriteTexture &spriteTexture) override;
  };
}
