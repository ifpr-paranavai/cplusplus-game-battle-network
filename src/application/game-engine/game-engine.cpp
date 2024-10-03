#include "game-engine.h"

namespace Game
{

  void GameEngine::startGame()
  {
    auto &windowManager = Global::adaptersInstance.windowManager;
    auto &keyboardManager = Global::adaptersInstance.keyboardManager;
    auto &timeManager = Global::adaptersInstance.timeManager;
    auto &renderer = Global::adaptersInstance.renderer;

    windowManager->createWindow(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT);

    MainMenu mainMenu;
    Global::gameStateService->pushGameState(&mainMenu);
    // std::unique_ptr<Player> player = std::make_unique<Player>();
    // Arena arena;
    // arena.setPlayer(player.get());

    while (!keyboardManager->exitEventIsCalled())
    {
      timeManager->updateTime();
      // arena.render();
      // mainMenu.render();
      Global::gameStateService->renderCurrentState();
      renderer->updateScreen();
    }
  }

}
