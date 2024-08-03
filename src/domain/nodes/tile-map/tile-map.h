#pragma once
#include <list>
#include "../tile/tile.h"
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../../utils/math/vector.h"
#include "../../../config/config.h"

namespace Game
{
    class TileMap
    {
    private:
        static const int tilesColumnsCount = 6;
        static const int tilesRowsCount = 3;
        static const int tileSpacing = 10;
        static const int tileWidth = (Config::WINDOW_WIDTH - (tilesColumnsCount + 1) * tileSpacing) / TileMap::tilesColumnsCount;
        static const int tileHeight = TileMap::tileWidth / 2.5;
        static const int tilesStartY = Config::WINDOW_HEIGHT - (TileMap::tilesRowsCount * (TileMap::tileHeight + TileMap::tileSpacing));

        std::list<Tile> tiles;
        int playerColumnTilesCount = 3;
        int enemyColumnTilesCount = TileMap::tilesColumnsCount - this->playerColumnTilesCount;
        std::string playerTileColor = "#FF4500";
        std::string enemyTileColor = "#4169E1";

    public:
        TileMap();

        static Vector getElementPositionInTile(Vector tilePosition, int elementWidth, int elementHeight);

        void init();
        void render();
        int getPlayerColumnTilesCount();
        int getEnemyColumnTilesCount();
        int getTilesRowsCount();
    };
}