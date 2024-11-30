#include "actor.h"

namespace Game
{
  Actor::~Actor()
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

  void Actor::applyPendingAnimation()
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