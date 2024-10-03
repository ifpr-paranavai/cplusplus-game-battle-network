#include "main-menu.h"

namespace Game
{
  void MainMenu::verifySelectionComands()
  {
    const auto &keyboardManager = Global::adaptersInstance.keyboardManager;
    if (keyboardManager->isKeyPressed(KeyCode::ARROW_UP) && this->selectedOptionIndex > 0)
    {
      this->selectedOptionIndex--;
    }
    else if (keyboardManager->isKeyPressed(KeyCode::ARROW_DOWN) && this->selectedOptionIndex < this->options.size() - 1)
    {
      this->selectedOptionIndex++;
    }
  }

  void MainMenu::render()
  {
    this->verifySelectionComands();
    for (const auto bg : this->backgroundSprites)
    {
      bg.renderSprite(Vector(0, 0));
    }

    Global::adaptersInstance.renderer->renderText({this->title, this->titlePostion});

    for (int i = 0; i < this->options.size(); i++)
    {
      const int positionY = this->topPadding + (i + 1) * (this->spacing + this->textHeight);
      this->options[i].render(positionY, i == this->selectedOptionIndex);
    }
  }
}