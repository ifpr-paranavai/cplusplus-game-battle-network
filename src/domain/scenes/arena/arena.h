#pragma once
#include "../../../config/config.h"
#include "../player/player.h"
#include "../../nodes/tile-map/tile-map.h"
#include "../enemy/enemy.h"

namespace Game
{
    class Arena
    {
    private:
        RendererPort *renderer;
        VisualElement *background;
        Player *player;
        TileMap *tileMap;
        std::string backgroundColorHex = "#87CEEB";
        std::list<Enemy *> enemies;

        void configureBackground();
        void createEnemies();

    public:
        Arena(RendererPort *_renderer);

        void render();
        void setPlayer(Player *_player);
    };
}