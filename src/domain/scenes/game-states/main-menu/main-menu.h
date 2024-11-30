#pragma once
#include <vector>
#include "../../../nodes/menu-option/menu-option.h"
#include "../../../../config/config.h"
#include "../../../../utils/global-adapters/global-adapters.h"
#include "../../../../utils/observer/observer.h"
#include "./handlers.h"
#include "../../../nodes/menu/menu.h"

namespace Game
{
  class MainMenu : public Menu
  {
  private:
    static constexpr std::string_view tutorial = "Setas para navegar | Enter para selecionar";

    const Vector tutorialPosition = {
        static_cast<float>(Config::WINDOW_WIDTH) / 2.0f -
            static_cast<float>(Global::adaptersInstance.textRenderer->getTextWidth(this->tutorial)) / 2.0f,
        static_cast<float>(Config::WINDOW_HEIGHT) -
            static_cast<float>(Global::adaptersInstance.textRenderer->getTextHeight(this->tutorial)) -
            static_cast<float>(this->getSpacing())};

    const int textHeight = Global::adaptersInstance.textRenderer->getTextHeight("A");
    const Music mainMenuMusic = Global::adaptersInstance.audioManager->initMusic("assets/music/main-menu.mp3");

    std::vector<MenuOption> options;

  public:
    MainMenu();
    ~MainMenu()
    {
      Global::adaptersInstance.audioManager->freeMusic(this->mainMenuMusic);
    }
    void render(const Vector &basePosition = {0, 0}) const override;
  };

}