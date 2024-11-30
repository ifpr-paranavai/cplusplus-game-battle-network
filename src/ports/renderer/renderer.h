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
    const Vector position;
    const int width;
    const int height;
    const Color color;
  };

  struct CreateSpriteTextureData
  {
    const std::string_view path;
    const std::optional<Color> colorFilter;
  };

  struct RenderSpriteData
  {
    const SpriteTexture &spriteTexture;
    const Vector &position;
    const float width;
    const float height;
    const bool flipHorizontally = false;
    const bool flipVertically = false;
  };

  class RendererPort
  {
  public:
    virtual void renderElement(const RenderElementData &renderDataDTO) = 0;
    virtual void renderBorder(const RenderElementData &renderDataDTO) = 0;
    virtual void renderSprite(const RenderSpriteData &renderSpriteData) = 0;
    virtual void updateScreen() = 0;
    virtual void destroyRenderer() = 0;
    virtual SpriteTexture getSpriteTexture(const CreateSpriteTextureData &renderSpriteData) = 0;
    virtual void destroySpriteTexture(const SpriteTexture &spriteTexture) = 0;
  };
}
