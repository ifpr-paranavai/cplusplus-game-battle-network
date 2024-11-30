#pragma once
#include <memory>
#include <list>
#include <vector>
#include "../../../../config/config.h"
#include "../../player/player.h"
#include "../../tile-map/tile-map.h"
#include "../../enemies/fireman/fireman.h"
#include "../../../../utils/log-manager/log-manager.h"
#include "../../../global/global-services/global-services.h"
#include "../../../dto/music/music.h"
#include "../../../nodes/sprite/sprite.h"
#include "../../../../utils/observer/observer.h"
#include "../../card-selector/card-selector.h"
#include "../../../nodes/game-state/game-state.h"
#include "../../../../utils/time/time.h"
#include "../score-board/score-board.h"
#include "../../../../utils/timer-subject/timer-subject.h"
#include "../../game-states-modals/card-selector-delay-bar/card-selector-delay-bar.h"
#include "./handlers/handlers.h"
#include "../../../nodes/actor/actor.h"

namespace Game
{
  class Arena : public GameState
  {
  private:
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

    static constexpr int initialTutorialYPosition = Config::WINDOW_HEIGHT / 3;
    static constexpr float tutorialsDuration = 7.5f;

    const Music music = Global::adaptersInstance.audioManager->initMusic("assets/music/battle-music.mp3");
    const float arenaStartedAt = Global::adaptersInstance.timeManager->getElapsedTime();
    const int textHeight = Global::adaptersInstance.textRenderer->getTextHeight("A");
    const int spaceBetweenTutorials = 30 + textHeight;
    const std::vector<std::string_view> tutorials = {
        "X - Atirar / Selecionar",
        "Z - Abrir menu de cartas",
        "C - Usar Carta",
        "Setas - Mover"};

    bool showTutorials = true;
    bool canOpenCardSelector = false;
    TimerSubject removeTutorialsTimer;
    Player *player;
    TileMap tileMap;
    CardSelector cardSelector;
    CardSelectorDelayBar cardSelectorDelayBar;
    GameOverHandler gameOverHandler = GameOverHandler();
    VictoryHandler victoryHandler = VictoryHandler(this->arenaStartedAt);
    UnblockOpenCardSelectorHandler unblockOpenCardSelectorHandler = UnblockOpenCardSelectorHandler(*this);
    CloseCardSelectorDelayHandler closeCardSelectorDelayHandler = CloseCardSelectorDelayHandler(*this);
    std::list<Actor *> actors;

    void createEnemies();
    void updateAttacks();
    void updateAnimations();
    void checkKeyboard();
    void renderTutorials() const;
    void renderAttacks() const;
    void renderPlayerLife() const;
    void renderPlayedTime() const;

  public:
    Arena();
    ~Arena();
    void update() override;
    void render(const Vector &basePosition = {0, 0}) const override;
    void setPlayer(Player *_player);
  };
}