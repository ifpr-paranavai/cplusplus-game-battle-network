#include "tile-based-body.h"

namespace Game
{
    TileBasedBody::TileBasedBody(int width, int height) : Element(width, height) {}

    void TileBasedBody::setTilePosition(Vector tilePosition)
    {
        this->tilePosition = tilePosition;
        this->position = TileMap::getElementPositionInTile(this->tilePosition, this->width, this->height);
    }

    void TileBasedBody::setTileXLimit(Vector tileXLimit)
    {
        this->tileXLimit = tileXLimit;
    }

    void TileBasedBody::setTileYLimit(Vector tileYLimit)
    {
        this->tileYLimit = tileYLimit;
    }

    bool TileBasedBody::tryMoveUp()
    {
        if (this->tilePosition.y - 1 < this->tileYLimit[0])
        {
            return false;
        }
        this->setTilePosition({this->tilePosition.x, this->tilePosition.y - 1});
        return true;
    }

    bool TileBasedBody::tryMoveDown()
    {

        if (this->tilePosition.y + 1 > this->tileYLimit[1])
        {
            return false;
        }
        this->setTilePosition({this->tilePosition.x, this->tilePosition.y + 1});
        return true;
    }

    bool TileBasedBody::tryMoveLeft()
    {
        if (this->tilePosition.x - 1 < this->tileXLimit[0])
        {
            return false;
        }
        this->setTilePosition({this->tilePosition.x - 1, this->tilePosition.y});
        return true;
    }

    bool TileBasedBody::tryMoveRight()
    {
        if (this->tilePosition.x + 1 > this->tileXLimit[1])
        {
            return false;
        }
        this->setTilePosition({this->tilePosition.x + 1, this->tilePosition.y});
        return true;
    }
}