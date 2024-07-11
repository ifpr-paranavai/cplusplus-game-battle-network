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
                tile->setConfig(hexColor, posX, posY, this->tileWidth, this->tileHeight);
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

    int TileMap::getElementInTilePositionX(int tileColIndex, int elementWidth)
    {
        int posX = tileColIndex * (tileWidth + tileSpacing) + tileSpacing + (tileWidth - elementWidth) / 2;
        return posX;
    }

    int TileMap::getElementInTilePositionY(int tileRowIndex, int elementHeight)
    {
        int heightAdjust = elementHeight < TileMap::tileHeight ? (TileMap::tileHeight - elementHeight) : 0;
        int posY = tilesStartY + tileRowIndex * (tileHeight + tileSpacing) - tileHeight / 2 + heightAdjust;
        return posY;
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