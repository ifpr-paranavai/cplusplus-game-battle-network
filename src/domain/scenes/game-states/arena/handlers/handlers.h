#pragma once
#include "../../../../../utils/global-adapters/global-adapters.h"
#include "../../../../../utils/observer/observer.h"
#include "../../../../enums/game-states-routes.h"
#include "../../score-register/score-register-params.h"
#include "../../../../nodes/game-state/game-state.h"
#include "../../../../global/global-services/global-services.h"
#include "../../../../dto/music/music.h"

namespace Game
{
  class VictoryHandler : public Observer<int>
  {
  private:
    const float arenaStartedAt;

  public:
    VictoryHandler(const float _arenaStartedAt) : arenaStartedAt(_arenaStartedAt) {}

    void next(const int &value) override
    {
      const float playedTime = Global::adaptersInstance.timeManager->getElapsedTime() - this->arenaStartedAt;
      ScoreRegisterParams scoreParams = {playedTime};
      GameStateRouteParams<std::any> gameStateRoute{scoreParams};
      Global::gameStateService->replace(GameStateRoute::SCORE_REGISTER, gameStateRoute);
    }
  };

  class GameOverHandler : public Observer<int>
  {
  private:
    const Music gameOverMusic = Global::adaptersInstance.audioManager->initMusic("assets/music/game-over-yeah.mp3");

  public:
    void next(const int &value) override
    {
      Global::adaptersInstance.audioManager->playMusic(this->gameOverMusic);
      Global::gameStateService->replace(GameStateRoute::SCORE_BOARD);
    }
  };
}