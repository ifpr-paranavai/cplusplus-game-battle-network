#include "character.h"

namespace Game
{

    Character::Character(
        RendererPort *_renderer,
        TimeManagerPort *_timeManager,
        int width,
        int height,
        std::string_view hexColor) : renderer(_renderer),
                                     Element(_timeManager, width, height),
                                     sprite(_renderer)

    {
        this->width = width;
        this->height = height;
        this->sprite.setConfig(hexColor, this->position, this->width, this->height);
    }

    void Character::setTilePosition(Vector tilePosition)
    {
        this->tilePosition = tilePosition;
        this->position = TileMap::getElementPositionInTile(this->tilePosition, this->width, this->height);
    }

    int Character::getWidth()
    {
        return this->width;
    }

    int Character::getHeight()
    {
        return this->height;
    }

    void Character::setTileLimits(
        int initialTileColumnIndex,
        int finalTileColumnIndex,
        int initialTileRowIndex,
        int finalTileRowIndex)
    {
        this->initialTileColumnLimit = initialTileColumnIndex;
        this->initialTileRowLimit = initialTileRowIndex;
        this->finalTileColumnLimit = finalTileColumnIndex;
        this->finalTileRowLimit = finalTileRowIndex;
    }

    void Character::render()
    {
        this->sprite.setPosition(this->position);
        this->sprite.renderSprite();
        Vector textPosition = Vector(this->position.x, this->position.y + this->height + 5);
        this->renderer->renderText(std::to_string(this->life), textPosition);
    }

}
