#pragma once
#include <list>
#include "../../nodes/visual-entity/visual-entity.h"
#include "../tile/tile.h"
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../dto/vector/vector.h"
#include "../../../config/config.h"

namespace Game
{
    class TileMap : public VisualEntity
    {
    private:
        static constexpr int tilesColumnsCount = 6;
        static constexpr int tilesRowsCount = 3;
        static constexpr int tileSpacing = 10;
        static constexpr int tileBottomMargin = 20;
        static constexpr int tileWidth = (Config::WINDOW_WIDTH - (tilesColumnsCount + 1) * tileSpacing) / TileMap::tilesColumnsCount;
        static constexpr int tileHeight = TileMap::tileWidth / 2.5;
        static constexpr int tilesStartY = Config::WINDOW_HEIGHT - (TileMap::tilesRowsCount * (TileMap::tileHeight + TileMap::tileSpacing)) - TileMap::tileBottomMargin;

        std::list<Tile> tiles;
        int playerColumnTilesCount = 3;
        int enemyColumnTilesCount = TileMap::tilesColumnsCount - this->playerColumnTilesCount;

    public:
        TileMap();

        // TODO: Incorrect responsability
        static Vector getElementPositionInTile(Vector tilePosition, int elementWidth, int elementHeight);

        void update() override {}
        void render() const override;
        int getPlayerColumnTilesCount();
        int getEnemyColumnTilesCount();
        int getTilesRowsCount();
    };
}