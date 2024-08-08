#include "tile-map.h"

namespace Game
{
    TileMap::TileMap() {}

    void TileMap::init()
    {
        for (int i = 0; i < this->tilesColumnsCount; ++i)
        {
            for (int j = 0; j < this->tilesRowsCount; ++j)
            {
                const int posX = i * (tileWidth + tileSpacing) + tileSpacing;
                const int posY = this->tilesStartY + (j * (this->tileHeight + this->tileSpacing));
                const bool isPlayerTile = i < this->playerColumnTilesCount;
                Tile tile = Tile(this->tileWidth, this->tileHeight, Vector(posX, posY), isPlayerTile);
                this->tiles.push_back(tile);
            }
        }
    }

    void TileMap::render()
    {
        for (const Tile &tile : this->tiles)
        {
            tile.renderSprites();
        }
    }

    Vector TileMap::getElementPositionInTile(Vector tilePosition, int elementWidth, int elementHeight)
    {
        const int heightAdjust = elementHeight < TileMap::tileHeight ? (TileMap::tileHeight - elementHeight) : 0;
        const int posX = tilePosition.x * (tileWidth + tileSpacing) + tileSpacing + (tileWidth - elementWidth) / 2;
        const int posY = TileMap::tilesStartY + tilePosition.y * (tileHeight + tileSpacing) - tileHeight / 2 + heightAdjust;
        return Vector(posX, posY);
    }

    int TileMap::getPlayerColumnTilesCount()
    {
        return this->playerColumnTilesCount;
    }

    int TileMap::getEnemyColumnTilesCount()
    {
        return this->enemyColumnTilesCount;
    }

    int TileMap::getTilesRowsCount()
    {
        return this->tilesRowsCount;
    }
}