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

    void Character::updateCurrentAnimatedSprite(AnimatedSprite *sprite)
    {
        if (this->currentAnimatedSprite != nullptr)
        {
            Global::animationService->removeAnimatedSprite(this->currentAnimatedSprite);
        }
        this->currentAnimatedSprite = sprite;
        Global::animationService->addAnimatedSprite(sprite);
    }

}
