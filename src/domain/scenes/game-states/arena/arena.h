#pragma once
#include <memory>
#include <list>
#include <vector>
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
#include "../score-board/score-board.h"
#include "../../../../utils/timer-subject/timer-subject.h"

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
        Global::gameStateService->replace(new ScoreRegister(playedTime, this->arena.backHandler));
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
        Global::gameStateService->replace(new ScoreBoard(this->arena.backHandler));
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

    class RemoveTutorialsHandler : public Observer<int>
    {
    private:
      Arena &arena;

    public: 
      RemoveTutorialsHandler(Arena &arena) : arena(arena) {}

      void next(const int &value) override
      {
        arena.showTutorials = false;
      }
    };

    const Music music = Global::adaptersInstance.audioManager->initMusic("assets/music/battle-music.mp3");
    const float arenaStartedAt = Global::adaptersInstance.timeManager->getElapsedTime();
    const int initialTutorialYPosition = Config::WINDOW_HEIGHT / 3;
    const int textHeight = Global::adaptersInstance.textRenderer->getTextHeight("A");
    const int spaceBetweenTutorials = 30 + textHeight;
    const std::vector<std::string> tutorials = {
      "X - Atirar / Selecionar",
      "Z - Abrir menu de cartas",
      "C - Usar Carta"
    };
    TimerSubject removeTutorialsTimer;
    bool showTutorials = true;
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
    Observer<int> *backHandler;
    bool canOpenCardSelector = false;
    int playerPoints = 0;

    void createEnemies();
    void updateAttacks();
    void updateAnimations();
    void checkKeyboard();
    void renderTutorials() const;
    void renderAttacks() const;
    void renderPlayerLife() const;
    void renderPlayedTime() const;
    void renderRunningMode() const;

  public:
    Arena(Observer<int> *backHandler);
    ~Arena();
    void update() override;
    void render() const override;
    void setPlayer(Player *_player);
  };
}