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
#include "../card-selector-delay-bar/card-selector-delay-bar.h"

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

    class UnblockOpenCardSelectorHandler : public Observer<int>
    {
    private:
      Arena &arena;

    public:
      UnblockOpenCardSelectorHandler(Arena &arena) : arena(arena) {}

      void next(const int &elapsedTime) override
      {
        this->arena.canOpenCardSelector = true;
      }
    };

    class CloseCardSelectorDelayHandler : public Observer<Card>
    {
    private:
      Arena &arena;

    public:
      CloseCardSelectorDelayHandler(Arena &arena) : arena(arena) {}

      void next(const Card &value) override
      {
        this->arena.cardSelectorDelayBar.resetTimer();
        this->arena.canOpenCardSelector = false;
        this->arena.arenaMode = ArenaMode::RUNNING;
      }
    };

    const Music music = Global::adaptersInstance.audioManager->initMusic("assets/music/battle-music.mp3");
    ArenaMode arenaMode = ArenaMode::RUNNING;
    Player *player;
    TileMap tileMap;
    CardSelector cardSelector;
    CardSelectorDelayBar cardSelectorDelayBar;
    GameOverHandler gameOverHandler = GameOverHandler(*this);
    VictoryHandler victoryHandler = VictoryHandler(*this);
    UnblockOpenCardSelectorHandler unblockOpenCardSelectorHandler = UnblockOpenCardSelectorHandler(*this);
    CloseCardSelectorDelayHandler closeCardSelectorDelayHandler = CloseCardSelectorDelayHandler(*this);
    std::list<Character *> characters;
    const std::vector<Sprite> backgroundSprites = {
        Sprite({Config::WINDOW_WIDTH,
                Config::WINDOW_HEIGHT,
                "assets/sprites/background/bg.png",
                false,
                Vector(0, 0)}),
        Sprite({Config::WINDOW_WIDTH,
                Config::WINDOW_HEIGHT,
                "assets/sprites/background/clouds.png",
                false,
                Vector(0, 0)})};
    bool canOpenCardSelector = false;

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