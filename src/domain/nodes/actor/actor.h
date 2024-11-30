#pragma once
#include "../tiled-game-object/tiled-game-object.h"
#include "../animated-sprited/animated-sprited.h"
#include "../../../utils/subject/subject.h"
#include "../../global/global-services/global-services.h"

namespace Game
{
  class Actor : public TiledGameObject
  {
  private:
    AnimatedSprite *currentAnimation = nullptr;
    AnimatedSprite *pendingAnimation = nullptr;

    void applyPendingAnimation();

  protected:
    int life = 0;
    Subject<int> onDeath;

    inline void queueAnimationChange(AnimatedSprite *newAnimation) { this->pendingAnimation = newAnimation; }

  public:
    ~Actor();

    inline int getLife() { return this->life; }
    inline void subscribeToDeath(Observer<int> *observer) { onDeath.subscribe(observer); }

    virtual void update() override
    {
      this->applyPendingAnimation();
    }

    void render(const Vector &basePosition = {0, 0}) const override
    {
      this->currentAnimation->render(this->position);
    }
  };
}
