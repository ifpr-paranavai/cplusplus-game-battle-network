#include "tile-map.h"

namespace Game
{
    TileMap::TileMap(RendererPort *_renderer) : renderer(_renderer) {}

    void TileMap::init()
    {
        for (int i = 0; i < this->tilesColumnsCount; ++i)
        {
            for (int j = 0; j < this->tilesRowsCount; ++j)
            {
                VisualElement *tile = new VisualElement(this->renderer);
                int posX = i * (tileWidth + tileSpacing) + tileSpacing;
                int posY = this->tilesStartY + (j * (this->tileHeight + this->tileSpacing));
                std::string_view hexColor = i < this->playerColumnTilesCount ? this->playerTileColor : this->enemyTileColor;
                tile->setConfig(hexColor, Vector(posX, posY), this->tileWidth, this->tileHeight);
                this->tiles.push_back(tile);
            }
        }
    }

    void TileMap::render()
    {
        for (VisualElement *tile : this->tiles)
        {
            tile->renderSprite();
        }
    }

    Vector TileMap::getElementPositionInTile(Vector tilePosition, int elementWidth, int elementHeight)
    {
        int heightAdjust = elementHeight < TileMap::tileHeight ? (TileMap::tileHeight - elementHeight) : 0;
        int posX = tilePosition.x * (tileWidth + tileSpacing) + tileSpacing + (tileWidth - elementWidth) / 2;
        int posY = tilesStartY + tilePosition.y * (tileHeight + tileSpacing) - tileHeight / 2 + heightAdjust;
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