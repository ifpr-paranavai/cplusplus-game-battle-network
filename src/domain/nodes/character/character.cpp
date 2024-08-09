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

    void Character::render()
    {
        for (const Sprite &sprite : this->sprites)
        {
            sprite.renderSprite(this->position);
        }
    }
}
