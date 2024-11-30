#pragma once
#include <iostream>
#include "../../../../utils/observer/observer.h"
#include "../../../enums/game-states-routes.h"
#include "../../../nodes/game-state/game-state.h"
#include "../../../global/global-services/global-services.h"
#include "../score-register/score-register-params.h"

namespace Game
{
  class QuitGameHandler : public Observer<int>
  {
  public:
    void next(const int &value) override
    {
      exit(0);
    }
  };

  class StartGameHandler : public Observer<int>
  {
  public:
    void next(const int &value) override
    {
      Global::gameStateService->pushGameState(GameStateRoute::ARENA);
    }
  };

  // NOTE: Only for test
  class OpenScoreRegisterHandler : public Observer<int>
  {
  public:
    void next(const int &value) override
    {
      ScoreRegisterParams scoreParams = {10.0f};
      GameStateRouteParams<std::any> gameStateRoute{scoreParams};
      Global::gameStateService->pushGameState(GameStateRoute::SCORE_REGISTER, gameStateRoute);
    }
  };

  class OpenScoreBoardHandler : public Observer<int>
  {
  public:
    void next(const int &value) override
    {
      Global::gameStateService->pushGameState(GameStateRoute::SCORE_BOARD);
    }
  };

}