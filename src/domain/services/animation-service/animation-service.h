#pragma once
#include <list>
#include <memory>
#include "../../nodes/animated-sprited/animated-sprited.h"

namespace Game
{
  class AnimationService
  {
  private:
    std::list<AnimatedSprite *> animatedSprites;

  public:
    ~AnimationService()
    {
      for (auto animatedSprite : this->animatedSprites)
      {
        delete animatedSprite;
      }
    }

    void addAnimatedSprite(AnimatedSprite *animatedSprite)
    {
      this->animatedSprites.push_back(animatedSprite);
    }

    void removeAnimatedSprite(AnimatedSprite *animatedSprite)
    {
      animatedSprites.remove(animatedSprite);
    }

    void updateAnimatedSprites()
    {
      for (auto animatedSprite : this->animatedSprites)
      {
        animatedSprite->update();
      }
    }
  };
}
