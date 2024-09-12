#include "character.h"

namespace Game
{

  Character::Character(const int width, const int height) : TileBasedBody(width, height)
  {
    this->width = width;
    this->height = height;
  }

  Character::~Character()
  {
    if (this->currentAnimation != nullptr)
    {
      delete this->currentAnimation;
    }
    if (this->pendingAnimation != nullptr)
    {
      delete this->pendingAnimation;
    }
  }

  void Character::applyPendingAnimation()
  {
    if (this->pendingAnimation == nullptr)
    {
      return;
    }

    if (this->currentAnimation != nullptr)
    {
      Global::animationService->removeAnimatedSprite(this->currentAnimation);
    }

    this->currentAnimation = this->pendingAnimation;
    this->pendingAnimation = nullptr;
    Global::animationService->addAnimatedSprite(this->currentAnimation);
  }
}
