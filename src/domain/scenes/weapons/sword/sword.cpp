#include "sword.h"

namespace Game
{
    Sword::Sword(const Vector _relativePosition) : Weapon(_relativePosition, 50)
    {
        this->queueAnimationChange(&this->idleAnimation);
        this->stabAnimation.addOnAnimationEndCallback(
            [this]()
            {
                this->canAttack = true;
                Global::attacksService->removeTileBasedAttack(this->stabAttackIt);
                this->queueAnimationChange(&this->idleAnimation);
            });
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