#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../../../ports/text-renderer/text-renderer.h"
#include "../renderer/renderer.h"

namespace Game
{
  class SDLTextRendererAdapter : public TextRendererPort
  {
  private:
    TTF_Font *font = nullptr;
    const int defaultFontSize = 26;

    SDL_Renderer *getRenderer();
    void setFontSize(const int fontSize);
    int getTextDimensions(std::string_view text, std::optional<int> fontSize, int *textWidth, int *textHeight);

  public:
    SDLTextRendererAdapter();
    ~SDLTextRendererAdapter();

    int getTextHeight(std::string_view text, std::optional<int> fontSize = std::nullopt) override;
    int getTextWidth(std::string_view text, std::optional<int> fontSize = std::nullopt) override;
    void renderText(const RenderTextData &renderTextData) override;
  };
}