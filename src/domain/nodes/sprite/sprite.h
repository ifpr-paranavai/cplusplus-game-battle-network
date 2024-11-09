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
    const Vector position;
    const std::optional<Color> spriteColorFilter;
    const std::optional<bool> flipVertically;
  };

  class Sprite : public VisualEntity
  {
  private:
    bool flipVertically = false;
    bool flipHorizontally = false;
    SpriteTexture spriteTexture;

  public:
    Sprite(const SpriteConfig &spriteConfig);

    void update() override {}

    void render(const Vector &basePosition = {0, 0}) const override
    {
      Global::adaptersInstance.renderer->renderSprite({this->spriteTexture,
                                                       basePosition + this->position,
                                                       static_cast<float>(this->width),
                                                       static_cast<float>(this->height),
                                                       this->flipHorizontally,
                                                       this->flipVertically});
    }

    inline void setFlipVertically(const bool flipVertically) { this->flipVertically = flipVertically; }
    inline void setFlipHorizontally(const bool flipHorizontally) { this->flipHorizontally = flipHorizontally; }

    void destroy()
    {
      Global::adaptersInstance.renderer->destroySpriteTexture(this->spriteTexture);
    }
  };
}