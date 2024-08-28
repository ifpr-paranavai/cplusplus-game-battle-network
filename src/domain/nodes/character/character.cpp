#include "character.h"

namespace Game
{

    Character::Character(
        int width,
        int height) : TileBasedBody(width, height)
    {
        this->width = width;
        this->height = height;
    }

    void Character::applyPendingAnimation()
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
