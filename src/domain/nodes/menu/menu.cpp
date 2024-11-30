#include "menu.h"

namespace Game
{

  Menu::Menu(const MenuConfig &config, DefaultRouteParams params) : GameState(params), title(config.title)
  {
    this->initInitialMenuOptionYPosition();
    this->initTitlePosition();
    this->initOptions(config.optionsData);
  }

  void Menu::initInitialMenuOptionYPosition()
  {
    const int titleHeight = Global::adaptersInstance.textRenderer->getTextHeight(this->title, this->titleFontSize);
    this->initialMenuOptionYPosition = this->topPadding + titleHeight + this->spacing;
  }

  void Menu::initTitlePosition()
  {
    const int titleWidth = Global::adaptersInstance.textRenderer->getTextWidth(this->title, this->titleFontSize);
    this->titlePosition = {
        static_cast<float>(Config::WINDOW_WIDTH) / 2.0f - static_cast<float>(titleWidth) / 2.0f,
        static_cast<float>(this->topPadding)};
  }

  void Menu::initOptions(const std::vector<MenuOptionData> optionsData)
  {
    int positionY = this->initialMenuOptionYPosition;
    for (const auto &option : optionsData)
    {
      this->options.emplace_back(MenuOption({option.text, positionY, option.handler}));
      positionY += this->spacing + this->textHeight;
    }

    if (options.size() == 0)
    {
      throw std::runtime_error("Menu must have at least one option");
    }

    this->options[this->selectedOptionIndex].setSelected(true);
  }

  void Menu::updateSelectedOption(const int newSelectedOptionIndex)
  {
    this->options[this->selectedOptionIndex].setSelected(false);
    this->selectedOptionIndex = newSelectedOptionIndex;
    this->options[this->selectedOptionIndex].setSelected(true);
  }

  void Menu::verifyComands()
  {
    const auto &keyboardManager = Global::adaptersInstance.keyboardManager;
    if (keyboardManager->isKeyPressed(KeyCode::ARROW_UP) && this->selectedOptionIndex > 0)
    {
      this->updateSelectedOption(this->selectedOptionIndex - 1);
    }
    else if (keyboardManager->isKeyPressed(KeyCode::ARROW_DOWN) && this->selectedOptionIndex < this->options.size() - 1)
    {
      this->updateSelectedOption(this->selectedOptionIndex + 1);
    }
    else if (keyboardManager->isKeyPressed(KeyCode::ENTER))
    {
      this->options.at(this->selectedOptionIndex).click();
    }
  }

  void Menu::update()
  {
    this->verifyComands();
  }

  void Menu::render(const Vector &basePosition) const
  {
    GameState::render(basePosition);
    Global::adaptersInstance.textRenderer->renderText({this->title, this->titlePosition, this->titleFontSize});
    for (int i = 0; i < this->options.size(); i++)
    {
      this->options[i].render();
    }
  }

}
