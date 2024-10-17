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

      auto currentState = this->currentStates.back();
      currentState->update();
      currentState->render();
    }

    void pushGameState(GameState *gameState)
    {
      this->currentStates.push_back(gameState);
    }

    void popGameState()
    {
      this->currentStates.pop_back();
    }

    void replace(GameState *gameState)
    {
      this->currentStates.clear();
      this->currentStates.push_back(gameState);
    }
  };
}