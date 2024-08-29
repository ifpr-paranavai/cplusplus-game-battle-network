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
#include "../../../utils/observer/observer.h"

namespace Game
{
  class GameOverObserver: public Observer<int> 
  {
    void next(const int& value) override {
      std::cout << "GAME OVER" << std::endl;
    }
  };

  class VictoryObserver: public Observer<int>
  {
    void next(const int& value) override {
      std::cout << "VICTORY" << std::endl;
    }
  };

  class Arena
  {
  private:
    Player *player;
    TileMap *tileMap;
    GameOverObserver gameOverObserver;
    VictoryObserver victoryObserver;
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