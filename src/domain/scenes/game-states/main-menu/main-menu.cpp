#include "main-menu.h"

namespace Game
{
  MainMenu::MainMenu()
  {

    Global::adaptersInstance.audioManager->playMusic(this->mainMenuMusic);
    this->initOptions();
    this->options[this->selectedOptionIndex].setSelected(true);
  }

  void MainMenu::initOptions()
  {
    constexpr int basicOptionsCount = 3;
    constexpr int debugOptionsCount = 1;
    constexpr int totalOptionsCount = Config::DEBUG ? basicOptionsCount + debugOptionsCount : basicOptionsCount;
    this->options.reserve(totalOptionsCount);

    struct OptionData
    {
      const std::string_view text;
      Observer<int> *handler;
    };

    OptionData basicOptions[] = {
        {"Iniciar", new StartGameHandler()},
        {"Placar", new OpenScoreBoardHandler()},
        {"Sair", new QuitGameHandler()}};

    int positionY = this->initialMenuOptionYPosition;
    for (const auto &option : basicOptions)
    {
      this->options.emplace_back(MenuOption({option.text, positionY, option.handler}));
      positionY += this->spacing + this->textHeight;
    }

    if (Config::DEBUG)
    {
      this->options.emplace_back(MenuOption({"Registrar Pontuação", positionY, new OpenScoreRegisterHandler()}));
    }
  }

  void MainMenu::updateSelectedOption(const int newSelectedOptionIndex)
  {
    this->options[this->selectedOptionIndex].setSelected(false);
    this->selectedOptionIndex = newSelectedOptionIndex;
    this->options[this->selectedOptionIndex].setSelected(true);
  }

  void MainMenu::verifyComands()
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
    Global::adaptersInstance.textRenderer->renderText({this->title, this->titlePosition, this->titleFontSize});

    for (int i = 0; i < this->options.size(); i++)
    {
      this->options[i].render();
    }
  }
}
