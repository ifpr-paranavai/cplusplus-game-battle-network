#pragma once
#include "../animated-sprited/animated-sprited.h"
#include "../../global/global-services/global-services.h"

namespace Game
{
  class Weapon
  {

  protected:
    class WeaponIdleModeHandler : public Observer<int>
    {
    private:
      Weapon &weapon;

    public:
      WeaponIdleModeHandler(Weapon &weapon) : weapon(weapon) {}

      void next(const int &value) override
      {
        this->weapon.canAttack = true;
        this->weapon.queueAnimationChange(&this->weapon.idleAnimation);
      }
    };

    const Vector relativePosition;
    const int damage;
    AnimatedSprite idleAnimation;
    AnimatedSprite *currentAnimation = nullptr;
    AnimatedSprite *pendingAnimation = nullptr;
    WeaponIdleModeHandler idleModeHandler;
    bool canAttack = true;

    void applyPendingAnimation();

    void queueAnimationChange(AnimatedSprite *newAnimation)
    {
      this->pendingAnimation = newAnimation;
    }

  public:
    Weapon(
        const Vector _relativePosition,
        const int _damage,
        AnimatedSprite _idleAnimation) : relativePosition(_relativePosition),
                                               damage(_damage),
                                               idleAnimation(_idleAnimation),
                                               idleModeHandler(*this)
    {
      this->queueAnimationChange(&this->idleAnimation);
    }

    virtual void attack(const Vector elementAbsolutePosition, const Vector elementTilePosition) = 0;

    void update()
    {
      this->applyPendingAnimation();
    }

    virtual void render(Vector elementAbsolutePosition)
    {
      if (this->currentAnimation == nullptr)
      {
        return;
      }
      this->currentAnimation->renderSprite(elementAbsolutePosition + this->relativePosition);
    }
  };
}