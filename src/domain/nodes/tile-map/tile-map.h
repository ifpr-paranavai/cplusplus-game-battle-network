#pragma once
#include <list>
#include "../tile/tile.h"
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../dto/vector/vector.h"
#include "../../../config/config.h"

namespace Game
{
    class TileMap
    {
    private:
        static constexpr int tilesColumnsCount = 6;
        static constexpr int tilesRowsCount = 3;
        static constexpr int tileSpacing = 10;
        static constexpr int tileBottomMargin = 20;
        static const int tileWidth = (Config::WINDOW_WIDTH - (tilesColumnsCount + 1) * tileSpacing) / TileMap::tilesColumnsCount;
        static const int tileHeight = TileMap::tileWidth / 2.5;
        static const int tilesStartY = Config::WINDOW_HEIGHT - (TileMap::tilesRowsCount * (TileMap::tileHeight + TileMap::tileSpacing)) - TileMap::tileBottomMargin;

        std::list<Tile> tiles;
        int playerColumnTilesCount = 3;
        int enemyColumnTilesCount = TileMap::tilesColumnsCount - this->playerColumnTilesCount;

    public:
        TileMap();

        static Vector getElementPositionInTile(Vector tilePosition, int elementWidth, int elementHeight);

        void init();
        void render() const;
        int getPlayerColumnTilesCount();
        int getEnemyColumnTilesCount();
        int getTilesRowsCount();
    };
}