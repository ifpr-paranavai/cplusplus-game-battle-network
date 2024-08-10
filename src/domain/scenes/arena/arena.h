#pragma once
#include <memory>
#include <list>
#include "../../../config/config.h"
#include "../player/player.h"
#include "../../nodes/tile-map/tile-map.h"
#include "../enemies/fireman/fireman.h"
#include "../../../utils/log-manager/log-manager.h"
#include "../../global/global-services/global-services.h"
#include "../../dto/music/music.h"
#include "../../nodes/sprite/sprite.h"

namespace Game
{
    class Arena
    {
    private:
        Player *player;
        TileMap *tileMap;
        std::string backgroundColorHex = "#87CEEB";
        std::list<Character *> characters;
        std::list<Sprite> backgroundSprites;
        const Music music = Global::adaptersInstance.audioManager->initMusic("assets/music/battle-music.mp3");

        void configureBackground();
        void createEnemies();
        void renderAttacks();
        void updateAttacks();
        void updateAnimations();
        void renderPlayerLife();
        void renderBackground();

    public:
        Arena();
        void render();
        void setPlayer(Player *_player);
    };
}