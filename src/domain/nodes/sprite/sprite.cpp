#include "sprite.h"

namespace Game
{
    Sprite::Sprite(const SpriteConfig &spriteConfig, Vector initialRelativePosition)
        : spriteTexture(Global::adaptersInstance.renderer->getSpriteTexture({spriteConfig.spritePath,
                                                                             spriteConfig.width,
                                                                             spriteConfig.height,
                                                                             spriteConfig.flipHorizontal,
                                                                             spriteConfig.spriteColorFilter})),
          relativePosition(initialRelativePosition)
    {
    }
}
