#pragma once
#include <vector>
#include "../../../nodes/menu-option/menu-option.h"
#include "../../../../config/config.h"
#include "../../../../utils/global-adapters/global-adapters.h"
#include "../../../../utils/observer/observer.h"
#include "./handlers.h"

namespace Game
{

  class MainMenu : public GameState
  {
  private:
    static constexpr int topPadding = 100;
    static constexpr int spacing = 50;
    static constexpr int titleFontSize = 40;

    const std::string title = "Battle Network CPLUSPLUS";
    const int titleWidth = Global::adaptersInstance.textRenderer->getTextWidth(this->title, this->titleFontSize);
    const int titleHeight = Global::adaptersInstance.textRenderer->getTextHeight(this->title, this->titleFontSize);
    const int textHeight = Global::adaptersInstance.textRenderer->getTextHeight("A");
    const int initialMenuOptionYPosition = this->topPadding + this->titleHeight + this->spacing;
    const Vector titlePosition = {Config::WINDOW_WIDTH / 2 - this->titleWidth / 2, this->topPadding};
    const Music mainMenuMusic = Global::adaptersInstance.audioManager->initMusic("assets/music/main-menu.mp3");

    std::vector<MenuOption> options;
    int selectedOptionIndex = 0;

    void verifyComands();
    void clickOnSelectedOption();
    void initOptions();
    void updateSelectedOption(const int newSelectedOptionIndex);

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