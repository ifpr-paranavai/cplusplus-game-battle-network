#pragma once
#include <any>
#include <optional>
#include "../../domain/dto/vector/vector.h"
#include "../../domain/dto/color/color.h"
#include "../../domain/dto/sprite-texture/sprite-texture.h"

namespace Game
{

  struct RenderElementData
  {
    Vector position;
    float width;
    float height;
    Color color;
  };

  struct RenderSpriteData
  {
    std::string_view path;
    float width;
    float height;
    bool flipHorizontal;
    std::optional<Color> colorFilter;
  };

  struct RenderTextData
  {
    std::string_view text;
    Vector position;
    std::optional<int> fontSize;
    std::optional<int> maxWidth;
  };

  class RendererPort
  {
  public:
    virtual int getTextHeight(std::string_view text) = 0;
    virtual int getTextWidth(std::string_view text) = 0;
    virtual void renderElement(const RenderElementData &renderDataDTO) = 0;
    virtual void renderBorder(const RenderElementData &renderDataDTO) = 0;
    virtual void renderSprite(const SpriteTexture &spriteTexture, Vector position) = 0;
    virtual void updateScreen() = 0;
    virtual void renderText(const RenderTextData &renderTextData) = 0;
    virtual void destroyRenderer() = 0;
    virtual SpriteTexture getSpriteTexture(const RenderSpriteData &renderSpriteData) = 0;
  };
}
