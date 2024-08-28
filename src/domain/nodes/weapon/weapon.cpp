#include "weapon.h"

namespace Game
{
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