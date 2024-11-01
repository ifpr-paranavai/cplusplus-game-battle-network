#include "menu-option.h"

namespace Game
{
  MenuOption::MenuOption(const MenuOptionConfig &config) : text(config.text)
  {
    const int textWidth = Global::adaptersInstance.textRenderer->getTextWidth(this->text);
    this->onClick.subscribe(config.onClick);
    this->position = {Config::WINDOW_WIDTH / 2 - textWidth / 2, config.yPosition};
    this->initRenderTextData();
  }

  void MenuOption::initRenderTextData()
  {
    this->renderTextData.text = this->text;
    this->renderTextData.position = this->position;
  }

  void MenuOption::setSelected(const bool isSelected)
  {
    this->isSelected = isSelected;
    this->renderTextData.color = isSelected ? Styles::Colors::SELECTED_COLOR : Styles::Colors::WHITE;
  }

  void MenuOption::render() const
  {
    Global::adaptersInstance.textRenderer->renderText(this->renderTextData);
  }
}
