#pragma once
#include "../animated-sprited/animated-sprited.h"
#include "../../global/global-services/global-services.h"

namespace Game
{
    class Weapon
    {
    protected:
        const Vector relativePosition;
        const int damage;
        AnimatedSprite *currentAnimation = nullptr;
        AnimatedSprite *pendingAnimation = nullptr;

        void applyPendingAnimation();

        void queueAnimationChange(AnimatedSprite *newAnimation)
        {
            this->pendingAnimation = newAnimation;
        }

    public:
        Weapon(const Vector _relativePosition, const int _damage) : relativePosition(_relativePosition), damage(_damage) {}

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