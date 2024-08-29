#include "sword.h"

namespace Game
{
  Sword::Sword(const Vector _relativePosition) : Weapon(_relativePosition, 50, AnimatedSprite({
                                                                                   0,
                                                                                   "assets/sprites/weapons/sword/idle",
                                                                                   1,
                                                                                   102,
                                                                                   20,
                                                                                   false,
                                                                                   Vector(0, 0),
                                                                               }))
  {
    this->stabAnimation.subscribeToAnimationEnd(new SwordIdleModeHandler(*this));
  }

  void Sword::attack(const Vector elementPosition, const Vector elementTilePosition)
  {
    if (!this->canAttack)
    {
      return;
    }

    this->canAttack = false;
    this->queueAnimationChange(&this->stabAnimation);
    auto stab = std::make_unique<Stab>(elementTilePosition, this->damage);
    this->stabAttackIt = Global::attacksService->addTileBasedAttack(std::move(stab));
  }
}