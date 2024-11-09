#include "main-menu.h"

namespace Game
{
  MainMenu::MainMenu() : Menu({"Battle Network CPLUSPLUS",
                               {{"Iniciar", new StartGameHandler()},
                                {"Placar", new OpenScoreBoardHandler()},
                                {"Sair", new QuitGameHandler()}}})
  {
    Global::adaptersInstance.audioManager->playMusic(this->mainMenuMusic);
  }

  void MainMenu::render(const Vector &basePosition) const
  {
    Menu::render();
    Global::adaptersInstance.textRenderer->renderText({this->tutorial, this->tutorialPosition});
  }
}
