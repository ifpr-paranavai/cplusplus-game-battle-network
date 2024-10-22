#pragma once
#include <vector>
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
  

  class QuitGameHandler : public Observer<int>
  {
  public:
    void next(const int &value) override
    {
      exit(0);
    }
  };
  
  class MainMenu : public GameState
  {
  private:
    class BackToMainMenuHandler : public Observer<int>
    {
    public:
      void next(const int &value) override
      {
        Global::gameStateService->replace(new MainMenu());
      }
    };

    class StartGameHandler : public Observer<int>
    {
    public:
      void next(const int &value) override
      {
        Global::gameStateService->pushGameState(new Arena(new BackToMainMenuHandler()));
      }
    };

    // NOTE: Only for test
    class OpenScoreRegisterHandler : public Observer<int>
    {
    public:
      void next(const int &value) override
      {
        Global::gameStateService->pushGameState(new ScoreRegister(1000.0f, new BackToMainMenuHandler()));
      }
    };

    class OpenScoreBoardHandler : public Observer<int>
    {
    public:
      void next(const int &value) override
      {
        Global::gameStateService->pushGameState(new ScoreBoard(new BackToMainMenuHandler()));
      }
    };

    static constexpr int topPadding = 100;
    static constexpr int spacing = 50;
    static constexpr int titleFontSize = 40;
    const Music mainMenuMusic = Global::adaptersInstance.audioManager->initMusic("assets/music/main-menu.mp3");
    const std::string title = "Battle Network CPLUSPLUS";
    const int titleWidth = Global::adaptersInstance.textRenderer->getTextWidth(this->title, this->titleFontSize);
    const int titleHeight = Global::adaptersInstance.textRenderer->getTextHeight(this->title, this->titleFontSize);
    const int textHeight = Global::adaptersInstance.textRenderer->getTextHeight("A");
    const Vector titlePostion = {Config::WINDOW_WIDTH / 2 - titleWidth / 2, 100};
    std::vector<MenuOption> options = {
        MenuOption("Iniciar", new StartGameHandler()),
        MenuOption("Placar", new OpenScoreBoardHandler()),        
        MenuOption("Sair", new QuitGameHandler())};
    int selectedOptionIndex = 0;

    void verifyComands();
    void clickOnSelectedOption();

  public:
    MainMenu();
    ~MainMenu()
    {
      Global::adaptersInstance.audioManager->freeMusic(this->mainMenuMusic);
    }
    void update() override;
    void render() const override;
  };

  
  

}