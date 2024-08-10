#include "animated-sprited.h"

namespace Game
{
    AnimatedSprite::AnimatedSprite(const AnimatedSpriteConfig &config) : spriteDisplayTime(config.spriteDisplayTime)
    {
        this->sprites.reserve(config.spritesPath.size());

        for (const auto &spritePath : config.spritesPath)
        {
            SpriteConfig spriteConfig{
                config.width,
                config.height,
                spritePath,
                config.flipHorizontal,
                config.initialRelativePosition,
                config.spriteColorFilter};
            this->sprites.emplace_back(std::move(spriteConfig));
        }
    }

    void AnimatedSprite::update()
    {
        this->elapsedTime += Global::adaptersInstance.timeManager->getDeltaTime();
        if (this->elapsedTime > this->spriteDisplayTime)
        {
            this->elapsedTime -= this->spriteDisplayTime;
            this->currentSpriteIndex = (this->currentSpriteIndex + 1) % this->sprites.size();
        }
    }

    void AnimatedSprite::renderSprite(Vector elementPosition) const
    {
        this->sprites[currentSpriteIndex].renderSprite(elementPosition);
    }

}