#pragma once
#include <string_view>
#include <optional>
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../dto/sprite-texture/sprite-texture.h"
#include "../../dto/color/color.h"
#include "../../dto/vector/vector.h"

namespace Game
{

  struct SpriteConfig
  {
    float width;
    float height;
    std::string_view spritePath;
    bool flipHorizontal;
    Vector initialRelativePosition;
    std::optional<Color> spriteColorFilter;
  };

  class Sprite
  {
  private:
    const SpriteTexture spriteTexture;
    Vector relativePosition;

  public:
    Sprite(const SpriteConfig &spriteConfig);

    void renderSprite(const Vector elementPosition) const
    {
      Global::adaptersInstance.renderer->renderSprite(this->spriteTexture, elementPosition + this->relativePosition);
    }

    void setRelativePosition(Vector relativePosition)
    {
      this->relativePosition = relativePosition;
    }
  };
}