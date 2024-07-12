#include "character.h"

namespace Game
{

    Character::Character(RendererPort *_renderer, int width, int height, std::string_view hexColor) : renderer(_renderer), Element(width, height)
    {
        this->width = width;
        this->height = height;
        this->sprite = new VisualElement(_renderer);
        this->sprite->setConfig(hexColor, 0, 0, this->width, this->height);
    }

    void Character::setTileCoords(int tileColumnIndex, int tileRowIndex)
    {
        this->tileColumnIndex = tileColumnIndex;
        this->tileRowIndex = tileRowIndex;
        this->positionX = TileMap::getElementInTilePositionX(this->tileColumnIndex, this->width);
        this->positionY = TileMap::getElementInTilePositionY(this->tileRowIndex, this->height);
    }

    void Character::setTileColumnIndex(int tileColumnIndex)
    {
        this->tileColumnIndex = tileColumnIndex;
        this->positionX = TileMap::getElementInTilePositionX(this->tileColumnIndex, this->width);
    }

    void Character::setTileRowIndex(int tileRowIndex)
    {
        this->tileRowIndex = tileRowIndex;
        this->positionY = TileMap::getElementInTilePositionY(this->tileRowIndex, this->height);
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
        this->sprite->setPosition(this->positionX, this->positionY);
        this->sprite->renderSprite();
        this->renderer->renderText(std::to_string(this->life), this->positionX, this->positionY + this->height + 5);
    }

}
