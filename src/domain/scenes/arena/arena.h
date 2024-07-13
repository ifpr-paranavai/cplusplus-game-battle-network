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
        RendererPort *renderer;
        VisualElement *background;
        Player *player;
        TileMap *tileMap;
        TimeManagerPort *timeManager;
        std::string backgroundColorHex = "#87CEEB";
        std::list<Enemy *> enemies;

        void configureBackground();
        void createEnemies();

    public:
        Arena(RendererPort *_renderer, TimeManagerPort *_timeManager);
        void render();
        void setPlayer(Player *_player);
    };
}