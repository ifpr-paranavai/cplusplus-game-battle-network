#include "sword.h"

namespace Game
{
  Sword::Sword(const ChildWeaponConfig swordConfig) : Weapon({swordConfig.relativePosition,
                                                              50,
                                                              AnimatedSprite({
                                                                  0,
                                                                  "assets/sprites/weapons/sword/idle",
                                                                  1,
                                                                  102,
                                                                  20,
                                                                  false,
                                                                  Vector(0, 0),
                                                              }),
                                                              swordConfig.attackInitObserver,
                                                              swordConfig.attackEndObserver})
  {
    this->stabAnimation.subscribeToAnimationEnd(new SwordIdleModeHandler(*this));
    this->stabAnimation.subscribeToAnimationEnd(swordConfig.attackEndObserver);
  }

  void Sword::attack(const Vector elementPosition, const Vector elementTilePosition)
  {
    if (!this->canAttack)
    {
      return;
    }

    this->canAttack = false;
    this->onAttackInitSubject.next(0);
    this->queueAnimationChange(&this->stabAnimation);
    auto stab = std::make_unique<Stab>(elementTilePosition, this->damage);
    this->stabAttackIt = Global::attacksService->addTileBasedAttack(std::move(stab));
  }
}