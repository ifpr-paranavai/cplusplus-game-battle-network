#pragma once
#include <memory>
#include <list>
#include "../../../config/config.h"
#include "../player/player.h"
#include "../../nodes/tile-map/tile-map.h"
#include "../enemies/fireman/fireman.h"
#include "../../../utils/log-manager/log-manager.h"
#include "../../global/global-services/global-services.h"

namespace Game
{
    class Arena
    {
    private:
        VisualElement background;
        Player *player;
        TileMap *tileMap;
        std::string backgroundColorHex = "#87CEEB";
        std::list<Character *> characters;
        std::list<VisualElement> backgroundSprites;

        void configureBackground();
        void createEnemies();
        void renderAttacks();
        void updateAttacks();
        void renderPlayerLife();
        void renderBackground();

    public:
        Arena();
        void render();
        void setPlayer(Player *_player);
    };
}