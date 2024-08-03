#include "character.h"

namespace Game
{

    Character::Character(
        int width,
        int height,
        std::string_view hexColor) : TileBasedBody(width, height)
    {
        this->width = width;
        this->height = height;
        this->sprite.setConfig(hexColor, this->position, this->width, this->height);
    }

    void Character::render()
    {
        this->sprite.setPosition(this->position);
        this->sprite.renderSprite();
    }
}
