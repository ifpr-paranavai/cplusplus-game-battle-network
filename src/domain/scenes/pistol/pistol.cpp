#include "pistol.h"

namespace Game
{

    Pistol::Pistol(Vector _relativePosition) : relativePosition(_relativePosition)
    {
        this->updateCurrentAnimation(&this->idleAnimation);
        this->shootAnimation.addOnAnimationEndCallback(
            [this]()
            {
                this->updateCurrentAnimation(&this->idleAnimation);
            });
    }

    void Pistol::updateCurrentAnimation(AnimatedSprite *animation)
    {
        if (this->currentAnimation != nullptr)
        {
            Global::animationService->removeAnimatedSprite(this->currentAnimation);
        }
        this->currentAnimation = animation;
        Global::animationService->addAnimatedSprite(animation);
    }

    void Pistol::attack()
    {
        this->updateCurrentAnimation(&this->shootAnimation);
    }

}