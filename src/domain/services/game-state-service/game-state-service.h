#pragma once
#include <list>
#include "../../nodes/game-state/game-state.h"

namespace Game
{
  class GameStateService
  {
  private:
    std::list<GameState *> currentStates;

  public:
    void renderCurrentState()
    {
      if (this->currentStates.empty()) [[unlikely]]
      {
        return;
      }

      this->currentStates.back()->render();
    }

    void pushGameState(GameState *gameState)
    {
      this->currentStates.push_back(gameState);
    }
  };
}