#include "main-menu.h"

namespace Game
{
  MainMenu::MainMenu()
  {
    if (Config::DEBUG)
    {
      this->options.push_back(MenuOption("Registrar Pontuação", new OpenScoreRegisterHandler()));
    }
    Global::adaptersInstance.audioManager->playMusic(this->mainMenuMusic);
  }

  void MainMenu::verifyComands()
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
    else if (keyboardManager->isKeyPressed(KeyCode::ENTER))
    {
      this->clickOnSelectedOption();
    }
  }

  void MainMenu::clickOnSelectedOption()
  {
    this->options.at(this->selectedOptionIndex).click();
  }

  void MainMenu::update()
  {
    this->verifyComands();
  }

  void MainMenu::render() const
  {
    GameState::render();

    Global::adaptersInstance.textRenderer->renderText({this->title, this->titlePostion, this->titleFontSize});

    for (int i = 0; i < this->options.size(); i++)
    {
      const int positionY = this->topPadding + this->titleHeight + (i + 1) * (this->spacing + this->textHeight);
      this->options[i].render(positionY, i == this->selectedOptionIndex);
    }
  }
}
