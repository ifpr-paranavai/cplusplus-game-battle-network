#pragma once
#include <list>
#include <any>
#include <optional>
#include "../../domain/nodes/game-state/game-state.h"
#include "../../domain/nodes/game-state-modal/game-state-modal.h"
#include "../../domain/enums/game-states-routes.h"

namespace Game
{
  class GameStateServicePort
  {
  public:
    virtual void renderCurrentState() = 0;
    virtual void pushGameState(GameStateRoute route, std::optional<GameStateRouteParams<std::any>> _params = std::nullopt) = 0;
    virtual void pushGameStateModal(GameStateModal *gameStateModal) = 0;
    virtual void popGameState() = 0;
    virtual void replace(GameStateRoute route, std::optional<GameStateRouteParams<std::any>> _params = std::nullopt) = 0;
  };
}