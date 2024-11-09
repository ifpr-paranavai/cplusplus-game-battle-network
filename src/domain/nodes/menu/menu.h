#pragma once
#include <string_view>
#include <vector>
#include "../game-state/game-state.h"
#include "../menu-option/menu-option.h"

namespace Game
{
  struct MenuOptionData
  {
    const std::string_view text;
    Observer<int> *handler;
  };

  struct MenuConfig
  {
    const std::string_view title;
    const std::vector<MenuOptionData> optionsData;
  };

  class Menu : public GameState
  {
  private:
    static constexpr int topPadding = 100;
    static constexpr int spacing = 50;
    static constexpr int titleFontSize = 40;

    const int textHeight = Global::adaptersInstance.textRenderer->getTextHeight("A");
    const std::string_view title;

    int initialMenuOptionYPosition = 0;
    int selectedOptionIndex = 0;
    std::vector<MenuOption> options;
    Vector titlePosition;

    void initTitlePosition();
    void initInitialMenuOptionYPosition();
    void initOptions(const std::vector<MenuOptionData> optionsData);
    void updateSelectedOption(const int newSelectedOptionIndex);
    void verifyComands();

  protected:
    inline int getSpacing() const { return this->spacing; }

  public:
    Menu(const MenuConfig &config, DefaultRouteParams params = std::nullopt);
    void update() override;
    void render(const Vector &basePosition = {0, 0}) const override;
  };
}