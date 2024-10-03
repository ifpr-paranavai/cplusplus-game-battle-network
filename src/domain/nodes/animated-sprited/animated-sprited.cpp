#include "animated-sprited.h"

namespace Game
{
  AnimatedSprite::AnimatedSprite(const AnimatedSpriteConfig &config) : spriteDisplayTime(config.spriteDisplayTime)
  {
    this->sprites.reserve(config.animationFramesCount);

    for (int i = 0; i < config.animationFramesCount; i++)
    {
      auto fullSpritePath = std::string(config.animationFolderPath) + "/" + std::to_string(i) + ".png";
      SpriteConfig spriteConfig{
          config.width,
          config.height,
          fullSpritePath,
          config.flipHorizontal,
          config.initialRelativePosition,
          config.spriteColorFilter};
      this->sprites.emplace_back(std::move(spriteConfig));
    }
  }

  AnimatedSprite::~AnimatedSprite()
  {
    for (auto sprite : this->sprites)
    {
      sprite.destroy();
    }
  }

  void AnimatedSprite::update()
  {
    if (this->spriteDisplayTime == 0 || this->sprites.empty()) [[unlikely]]
    {
      return;
    }

    this->elapsedTime += Global::adaptersInstance.timeManager->getDeltaTime();
    if (this->elapsedTime > this->spriteDisplayTime)
    {
      this->elapsedTime -= this->spriteDisplayTime;
      this->currentSpriteIndex = (this->currentSpriteIndex + 1) % this->sprites.size();

      if (this->currentSpriteIndex == 0)
      {
        this->onAnimationEnd.next(0);
      }
    }
  }

  void AnimatedSprite::renderSprite(const Vector elementPosition) const
  {
    if (!this->sprites.empty() && currentSpriteIndex < this->sprites.size())
    {
      this->sprites[currentSpriteIndex].renderSprite(elementPosition);
    }
  }

}