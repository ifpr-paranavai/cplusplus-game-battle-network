#include "animated-sprited.h"

namespace Game
{
  AnimatedSprite::AnimatedSprite(const AnimatedSpriteConfig &config) : spriteDisplayTime(config.spriteDisplayTime)
  {
    this->width = config.width;
    this->height = config.height;
    this->flipHorizontally = config.flipHorizontal;
    this->position = config.position;
    this->initSprites(config);
  }

  AnimatedSprite::~AnimatedSprite()
  {
    for (auto spriteTexture : this->spriteTextures)
    {
      Global::adaptersInstance.renderer->destroySpriteTexture(spriteTexture);
    }
  }

  void AnimatedSprite::initSprites(const AnimatedSpriteConfig &config)
  {
    this->spriteTextures.reserve(config.animationFramesCount);
    for (int i = 0; i < config.animationFramesCount; i++)
    {
      auto fullSpritePath = std::string(config.animationFolderPath) + "/" + std::to_string(i) + ".png";
      SpriteTexture spriteTexture = Global::adaptersInstance.renderer->getSpriteTexture({fullSpritePath,
                                                                                         config.spriteColorFilter});
      this->spriteTextures.push_back(spriteTexture);
    }
  }

  void AnimatedSprite::update()
  {
    if (this->spriteDisplayTime == 0 || this->spriteTextures.empty()) [[unlikely]]
    {
      return;
    }

    this->elapsedTime += Global::adaptersInstance.timeManager->getDeltaTime();
    if (this->elapsedTime > this->spriteDisplayTime)
    {
      this->elapsedTime -= this->spriteDisplayTime;
      this->currentSpriteIndex = (this->currentSpriteIndex + 1) % this->spriteTextures.size();

      if (this->currentSpriteIndex == 0)
      {
        this->onAnimationEnd.next(0);
      }
    }
  }

  void AnimatedSprite::render(const Vector &basePosition) const
  {
    if (this->currentSpriteIndex < this->spriteTextures.size())
    {
      Global::adaptersInstance.renderer->renderSprite({this->spriteTextures[this->currentSpriteIndex],
                                                       basePosition + this->position,
                                                       static_cast<float>(this->width),
                                                       static_cast<float>(this->height),
                                                       this->flipHorizontally,
                                                       this->flipVertically});
    }
  }

}