#pragma once
#include <string_view>
#include <optional>
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../dto/sprite-texture/sprite-texture.h"
#include "../../dto/color/color.h"
#include "../../dto/vector/vector.h"
#include "../visual-entity/visual-entity.h"

namespace Game
{

  struct SpriteConfig
  {
    const int width;
    const int height;
    const std::string_view spritePath;
    const bool flipHorizontal;
    const Vector initialRelativePosition;
    const std::optional<Color> spriteColorFilter;
  };

  class Sprite
  {
  private:
    SpriteTexture spriteTexture;
    Vector relativePosition;

  public:
    Sprite(const SpriteConfig &spriteConfig);

    void renderSprite(const Vector elementPosition, std::optional<bool> flipVertically = std::nullopt) const
    {
      auto spriteTexture = this->spriteTexture;
      if (flipVertically.has_value() && flipVertically.value())
      {
        spriteTexture.flipVertically = true;
      }
      Global::adaptersInstance.renderer->renderSprite(spriteTexture, elementPosition + this->relativePosition);
    }

    inline void setRelativePosition(const Vector relativePosition) { this->relativePosition = relativePosition; }
    inline void setWidth(const float width) { this->spriteTexture.width = width; }
    inline void setHeight(const float height) { this->spriteTexture.height = height; }
    inline float getWidth() const { return this->spriteTexture.width; }
    inline float getHeight() const { return this->spriteTexture.height; }

    void destroy()
    {
      Global::adaptersInstance.renderer->destroySpriteTexture(this->spriteTexture);
    }
  };
}