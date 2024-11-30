#pragma once
#include "../../../nodes/menu/menu.h"
#include "../../../../utils/observer/observer.h"
#include "../../../global/global-services/global-services.h"
#include "../../../enums/game-states-routes.h"

namespace Game
{
  class ContinueHandler : public Observer<int>
  {
  public:
    void next(const int &value) override
    {
      Global::gameStateService->popGameState();
    }
  };

  class BackToMainMenuHandler : public Observer<int>
  {
  public:
    void next(const int &value) override
    {
      Global::gameStateService->replace(GameStateRoute::MAIN_MENU);
    }
  };

  class QuitHandler : public Observer<int>
  {
  public:
    void next(const int &value) override
    {
      exit(0);
    }
  };

  class Pause : public Menu
  {
  public:
    Pause();
  };
}