#include "menu-option.h"

namespace Game
{
  void MenuOption::render(const int yPosition, const bool isSelected)
  {
    const int textWidth = Global::adaptersInstance.renderer->getTextWidth(this->text);
    const Vector position = {Config::WINDOW_WIDTH / 2 - textWidth / 2, yPosition};

    RenderTextData renderTextData;
    renderTextData.text = this->text;
    renderTextData.position = position;
    if (isSelected)
    {
      renderTextData.color = this->selectedColor;
    }

    Global::adaptersInstance.renderer->renderText(renderTextData);
  }
}
