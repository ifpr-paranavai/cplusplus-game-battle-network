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

    int Character::getWidth()
    {
        return this->width;
    }

    int Character::getHeight()
    {
        return this->height;
    }

    void Character::render()
    {
        this->sprite.setPosition(this->position);
        this->sprite.renderSprite();
        const Vector textPosition = Vector(this->position.x, this->position.y + this->height + 5);
        Global::adaptersInstance.renderer->renderText(std::to_string(this->life), textPosition);
    }
}
