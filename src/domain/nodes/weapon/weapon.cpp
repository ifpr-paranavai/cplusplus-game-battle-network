#include "weapon.h"

namespace Game
{
  Weapon::Weapon(const WeaponConfig weaponConfig) : relativePosition(weaponConfig.relativePosition),
                                                    damage(weaponConfig.damage),
                                                    idleAnimation(weaponConfig.idleAnimation),
                                                    idleModeHandler(*this)
  {
    this->queueAnimationChange(this->idleAnimation);
    if (weaponConfig.attackInitObserver != nullptr)
    {
      this->onAttackInitSubject.subscribe(weaponConfig.attackInitObserver);
    }
    if (weaponConfig.attackEndObserver != nullptr)
    {
      this->onAttackEndSubject.subscribe(weaponConfig.attackEndObserver);
    }
  }

  void Weapon::applyPendingAnimation()
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