#pragma once
#include <list>
#include "../visual-element/visual-element.h"
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

        RendererPort *renderer;
        std::list<VisualElement *> tiles;
        int playerColumnTilesCount = 3;
        int enemyColumnTilesCount = TileMap::tilesColumnsCount - this->playerColumnTilesCount;
        std::string playerTileColor = "#FF4500";
        std::string enemyTileColor = "#4169E1";

    public:
        TileMap(RendererPort *_renderer);

        static int getElementInTilePositionX(int tileColIndex, int elementWidth);
        static int getElementInTilePositionY(int tileRowIndex, int elementHeight);

        void init();
        void render();
        int getPlayerColumnTilesCount();
        int getEnemyColumnTilesCount();
        int getTilesRowsCount();
    };
}