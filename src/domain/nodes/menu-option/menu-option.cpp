#include "menu-option.h"

namespace Game
{
  void MenuOption::render(const int yPosition, const bool isSelected) const
  {
    auto textRenderer = Global::adaptersInstance.textRenderer;
    const int textWidth = textRenderer->getTextWidth(this->text);
    const Vector position = {Config::WINDOW_WIDTH / 2 - textWidth / 2, yPosition};

    RenderTextData renderTextData;
    renderTextData.text = this->text;
    renderTextData.position = position;
    if (isSelected)
    {
      renderTextData.color = Styles::Colors::SELECTED_COLOR;
    }

    textRenderer->renderText(renderTextData);
  }
}
