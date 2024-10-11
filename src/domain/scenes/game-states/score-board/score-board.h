#pragma once
#include <list>
#include "../../../nodes/game-state/game-state.h"
#include "../../../global/global-services/global-services.h"
#include "../../../dto/score/score.h"
#include "../../../../utils/global-adapters/global-adapters.h"
#include "../../../nodes/menu-option/menu-option.h"
#include "../../../../utils/observer/observer.h"
#include "../../../../config/config.h"

namespace Game
{
  class BackToMainMenuHandler : public Observer<int>
  {
  public:
    void next(const int &value) override
    {
      Global::gameStateService->popGameState();
    }
  };

  class ScoreBoard : public GameState
  {
  private:
    std::list<Score> scores;
    MenuOption backOption = MenuOption("Voltar", new BackToMainMenuHandler());
    const int backOptionYPostion = Config::WINDOW_HEIGHT - Global::adaptersInstance.renderer->getTextHeight("Voltar") - 10;

    void loadScoresFromFile();
    void verifyCommands();

  public:
    ScoreBoard();
    void render() override;
  };
}