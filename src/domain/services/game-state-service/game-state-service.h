#pragma once
#include <list>
#include <any>
#include "../../../ports/game-state-service/game-state-service.h"
#include "../../nodes/game-state/game-state.h"
#include "../../enums/game-states-routes.h"
#include "../../consts/game-states-routes-map.h"
#include "../../nodes/game-state-modal/game-state-modal.h"

namespace Game
{
  class GameStateService : public GameStateServicePort
  {
  private:
    std::list<GameState *> currentStates;

  public:
    void renderCurrentState() override
    {
      if (this->currentStates.empty()) [[unlikely]]
      {
        return;
      }

      auto currentState = this->currentStates.back();
      currentState->update();
      currentState->render();
    }

    void pushGameState(GameStateRoute route, std::optional<GameStateRouteParams<std::any>> _params = std::nullopt) override
    {
      this->currentStates.push_back(GameStateRoutes::gameStatesRoutesMap.at(route)(_params));
    }

    void pushGameStateModal(GameStateModal *gameStateModal) override
    {
      this->currentStates.push_back(gameStateModal);
    }

    void popGameState() override
    {
      this->currentStates.pop_back();
    }

    void replace(GameStateRoute route, std::optional<GameStateRouteParams<std::any>> _params = std::nullopt) override
    {
      this->currentStates.clear();
      this->currentStates.push_back(GameStateRoutes::gameStatesRoutesMap.at(route)(_params));
    }
  };
}