#pragma once
#include "../../../config/config.h"
#include "../player/player.h"
#include "../../nodes/tile-map/tile-map.h"
#include "../enemy/enemy.h"
#include "../../../utils/log-manager/log-manager.h"

namespace Game
{
    class Arena
    {
    private:
        VisualElement *background;
        Player *player;
        TileMap *tileMap;
        std::string backgroundColorHex = "#87CEEB";
        std::list<Enemy *> enemies;

        void configureBackground();
        void createEnemies();

    public:
        Arena();
        void render();
        void setPlayer(Player *_player);
    };
}