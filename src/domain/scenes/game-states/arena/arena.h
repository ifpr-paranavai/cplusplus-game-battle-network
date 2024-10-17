#pragma once
#include <memory>
#include <list>
#include "../../../../config/config.h"
#include "../../player/player.h"
#include "../../../nodes/tile-map/tile-map.h"
#include "../../enemies/fireman/fireman.h"
#include "../../../../utils/log-manager/log-manager.h"
#include "../../../global/global-services/global-services.h"
#include "../../../dto/music/music.h"
#include "../../../nodes/sprite/sprite.h"
#include "../../../../utils/observer/observer.h"
#include "../../card-selector/card-selector.h"
#include "../../card-selector-delay-bar/card-selector-delay-bar.h"
#include "../../../nodes/game-state/game-state.h"
#include "../../../dto/score/score.h"
#include "../../../../utils/time/time.h"
#include "../score-register/score-register.h"

namespace Game
{
  enum class ArenaMode
  {
    VICTORY,
    GAME_OVER,
    RUNNING
  };

  class Arena : public GameState
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
        const float playedTime = Global::adaptersInstance.timeManager->getElapsedTime() - arena.arenaStartedAt;
        Global::gameStateService->replace(new ScoreRegister(playedTime));
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
        Global::gameStateService->popGameState();
      }
    };

    class PointsIncrementHandler : public Observer<Element *>
    {
    private:
      Arena &arena;

    public:
      PointsIncrementHandler(Arena &arena) : arena(arena) {}

      void next(Element *const &value) override
      {
        arena.playerPoints += 10;
      }
    };

    const Music music = Global::adaptersInstance.audioManager->initMusic("assets/music/battle-music.mp3");
    const float arenaStartedAt = Global::adaptersInstance.timeManager->getElapsedTime();
    ArenaMode arenaMode = ArenaMode::RUNNING;
    Player *player;
    TileMap tileMap;
    CardSelector cardSelector;
    CardSelectorDelayBar cardSelectorDelayBar;
    GameOverHandler gameOverHandler = GameOverHandler(*this);
    VictoryHandler victoryHandler = VictoryHandler(*this);
    UnblockOpenCardSelectorHandler unblockOpenCardSelectorHandler = UnblockOpenCardSelectorHandler(*this);
    CloseCardSelectorDelayHandler closeCardSelectorDelayHandler = CloseCardSelectorDelayHandler(*this);
    PointsIncrementHandler pointsIncrementHandler = PointsIncrementHandler(*this);
    std::list<Character *> characters;
    bool canOpenCardSelector = false;
    int playerPoints = 0;

    void createEnemies();
    void updateAttacks();
    void updateAnimations();
    void checkKeyboard();
    void renderAttacks() const;
    void renderPlayerLife() const;
    void renderPlayedTime() const;
    void renderRunningMode() const;

  public:
    Arena();
    ~Arena();
    void update() override;
    void render() const override;
    void setPlayer(Player *_player);
  };
}