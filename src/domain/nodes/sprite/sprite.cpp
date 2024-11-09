#include "sprite.h"

namespace Game
{
  Sprite::Sprite(const SpriteConfig &spriteConfig)
      : spriteTexture(Global::adaptersInstance.renderer->getSpriteTexture({spriteConfig.spritePath,
                                                                           spriteConfig.spriteColorFilter}))
  {
    this->position = spriteConfig.position;
    this->width = spriteConfig.width;
    this->height = spriteConfig.height;
    this->flipHorizontally = spriteConfig.flipHorizontal;
    this->flipVertically = spriteConfig.flipVertically.value_or(false);
  }
}
