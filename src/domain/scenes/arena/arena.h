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
#include "../card-selector/card-selector.h"

namespace Game
{
  enum class ArenaMode
  {
    VICTORY,
    GAME_OVER,
    RUNNING,
    CARD_SELECTOR_OPENED
  };

  class Arena
  {
  private:
    class VictoryHandler : public Observer<int>
    {
    private:
      Arena &arena;

    public:
      VictoryHandler(Arena &arena) : arena(arena) {}

      void next(const int &value) override
      {
        this->arena.arenaMode = ArenaMode::VICTORY;
      }
    };

    class GameOverHandler : public Observer<int>
    {
    private:
      Arena &arena;
      const Music gameOverMusic = Global::adaptersInstance.audioManager->initMusic("assets/music/game-over-yeah.mp3");

    public:
      GameOverHandler(Arena &arena) : arena(arena) {}

      void next(const int &value) override
      {
        this->arena.arenaMode = ArenaMode::GAME_OVER;
        Global::adaptersInstance.audioManager->playMusic(this->gameOverMusic);
      }
    };

    const Music music = Global::adaptersInstance.audioManager->initMusic("assets/music/battle-music.mp3");
    ArenaMode arenaMode = ArenaMode::RUNNING;
    Player *player;
    TileMap *tileMap;
    CardSelector cardSelector;
    GameOverHandler gameOverHandler;
    VictoryHandler victoryHandler;
    std::list<Character *> characters;
    std::list<Sprite> backgroundSprites;

    void configureBackground();
    void createEnemies();
    void renderAttacks();
    void updateAttacks();
    void updateAnimations();
    void renderPlayerLife();
    void renderBackground();
    void renderRunningMode();
    void checkKeyboard();

  public:
    Arena();
    void render();
    void setPlayer(Player *_player);
  };
}