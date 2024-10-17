#pragma once
#include <array>
#include "../../../nodes/menu-option/menu-option.h"
#include "../../../nodes/sprite/sprite.h"
#include "../../../../config/config.h"
#include "../../../../utils/global-adapters/global-adapters.h"
#include "../../../nodes/game-state/game-state.h"
#include "../../../global/global-services/global-services.h"
#include "../../../../utils/observer/observer.h"
#include "../arena/arena.h"
#include "../score-board/score-board.h"
#include "../score-register/score-register.h"

namespace Game
{
  class StartGameHandler : public Observer<int>
  {
  public:
    void next(const int &value) override
    {
      Global::gameStateService->pushGameState(new Arena());
    }
  };

  class QuitGameHandler : public Observer<int>
  {
  public:
    void next(const int &value) override
    {
      exit(0);
    }
  };

  class OpenScoreBoardHandler : public Observer<int>
  {
  public:
    void next(const int &value) override
    {
      Global::gameStateService->pushGameState(new ScoreBoard());
    }
  };

  // NOTE: Only for test
  class OpenScoreRegisterHandler : public Observer<int>
  {
  public:
    void next(const int &value) override
    {
      Global::gameStateService->pushGameState(new ScoreRegister(1000.0f));
    }
  };

  class MainMenu : public GameState
  {
  private:
    const int topPadding = 100;
    const int spacing = 50;
    const std::string title = "Main Menu";
    const int titleWidth = Global::adaptersInstance.textRenderer->getTextWidth(this->title);
    const int textHeight = Global::adaptersInstance.textRenderer->getTextHeight(this->title);
    const Vector titlePostion = {Config::WINDOW_WIDTH / 2 - titleWidth / 2, 100};
    std::array<MenuOption, 4> options = {
        MenuOption("Iniciar", new StartGameHandler()),
        MenuOption("Placar", new OpenScoreBoardHandler()),
        MenuOption("Registrar Pontuação", new OpenScoreRegisterHandler()),
        MenuOption("Sair", new QuitGameHandler())};
    int selectedOptionIndex = 0;

    void verifyComands();
    void clickOnSelectedOption();

  public:
    void update() override;
    void render() const override;
  };
}