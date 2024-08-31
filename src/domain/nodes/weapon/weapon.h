#pragma once
#include <memory>
#include "../animated-sprited/animated-sprited.h"
#include "../../global/global-services/global-services.h"
#include "../../../utils/observer/observer.h"
#include "../../../utils/subject/subject.h"

namespace Game
{
  struct WeaponConfig
  {
    Vector relativePosition;
    int damage;
    AnimatedSprite idleAnimation;
    Observer<int> *attackInitObserver;
    Observer<int> *attackEndObserver;
  };

  struct ChildWeaponConfig
  {
    Vector relativePosition;
    Observer<int> *attackInitObserver;
    Observer<int> *attackEndObserver;
  };

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
    Subject<int> onAttackInitSubject;
    Subject<int> onAttackEndSubject;

    void applyPendingAnimation();

    void queueAnimationChange(AnimatedSprite *newAnimation)
    {
      this->pendingAnimation = newAnimation;
    }

  public:
    Weapon(const WeaponConfig weaponConfig);

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