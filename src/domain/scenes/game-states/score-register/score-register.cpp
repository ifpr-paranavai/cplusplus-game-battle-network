#include "score-register.h"

namespace Game
{
  void ScoreRegister::verifyCommands()
  {
    auto keyboardManager = Global::adaptersInstance.keyboardManager;
    if (keyboardManager->isKeyPressed(KeyCode::ARROW_LEFT) && this->selectedLetterIndex > 0)
    {
      this->selectedLetterIndex--;
    }
    else if (keyboardManager->isKeyPressed(KeyCode::ARROW_RIGHT) && this->selectedLetterIndex < 2)
    {
      this->selectedLetterIndex++;
    }
  }

  void ScoreRegister::render()
  {
    this->verifyCommands();
    GameState::render();
    for (size_t i = 0; i < 3; i++)
    {
      RenderTextData renderTextData;
      renderTextData.text = std::string(1, this->playerNameLetters[i]);
      renderTextData.position = {this->initialLetterXPosition + (letterWidth + 10) * i, this->letterYPosition};
      if (this->selectedLetterIndex == i)
      {
        renderTextData.color = Styles::Colors::SELECTED_COLOR;
      }
      Global::adaptersInstance.textRenderer->renderText(renderTextData);
    }
  };

}