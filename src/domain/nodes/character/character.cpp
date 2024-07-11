#include "character.h"

namespace Game
{

    Character::Character(RendererPort *_renderer, int width, int height, std::string_view hexColor)
    {
        this->width = width;
        this->height = height;
        this->sprite = new VisualElement(_renderer);
        this->sprite->setConfig(hexColor, 0, 0, this->width, this->height);
    }

    void Character::setTilePosition(int tileColumnIndex, int tileRowIndex)
    {
        this->tileColumnIndex = tileColumnIndex;
        this->tileRowIndex = tileRowIndex;
    }

    int Character::getWidth()
    {
        return this->width;
    }

    int Character::getHeight()
    {
        return this->height;
    }

    void Character::setTileLimits(int tileColumnIndex, int tileRowIndex)
    {
        this->tileColumnIndexLimit = tileColumnIndex;
        this->tileRowLimit = tileRowIndex;
    }

    void Character::render()
    {
        int positionX = TileMap::getElementInTilePositionX(this->tileColumnIndex, this->width);
        int positionY = TileMap::getElementInTilePositionY(this->tileRowIndex, this->height);
        this->sprite->setTilePosition(positionX, positionY);
        this->sprite->renderSprite();
    }
}
