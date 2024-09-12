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
    std::unique_ptr<Player> player = std::make_unique<Player>();
    std::unique_ptr<Arena> arena = std::make_unique<Arena>();
    arena->setPlayer(player.get());

    while (!keyboardManager->exitEventIsCalled())
    {
      timeManager->updateTime();
      arena->render();
      renderer->updateScreen();
    }
  }

}
