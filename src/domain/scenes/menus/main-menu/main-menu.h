#pragma once
#include <array>
#include "../../../nodes/menu-option/menu-option.h"
#include "../../../nodes/sprite/sprite.h"
#include "../../../../config/config.h"
#include "../../../../utils/global-adapters/global-adapters.h"
#include "../../../nodes/game-state/game-state.h"
#include "../../../global/global-services/global-services.h"
#include "../../../../utils/observer/observer.h"
#include "../../arena/arena.h"

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

  class MainMenu : public GameState
  {
  private:
    const int topPadding = 100;
    const int spacing = 50;
    const std::string_view title = "Main Menu";
    const std::array<Sprite, 2> backgroundSprites = {
        Sprite({Config::WINDOW_WIDTH,
                Config::WINDOW_HEIGHT,
                "assets/sprites/background/bg.png",
                false,
                Vector(0, 0)}),
        Sprite({Config::WINDOW_WIDTH,
                Config::WINDOW_HEIGHT,
                "assets/sprites/background/clouds.png",
                false,
                Vector(0, 0)})};
    const int titleWidth = Global::adaptersInstance.renderer->getTextWidth(this->title);
    const int textHeight = Global::adaptersInstance.renderer->getTextHeight(this->title);
    const Vector titlePostion = {Config::WINDOW_WIDTH / 2 - titleWidth / 2, 100};
    std::array<MenuOption, 2> options = {
        MenuOption("Start", new StartGameHandler()), /**, MenuOption("Load"), MenuOption("Quit")*/
        MenuOption("Quit", new QuitGameHandler())};
    int selectedOptionIndex = 0;

    void verifyComands();
    void clickOnSelectedOption();

  public:
    void render() override;
  };
}