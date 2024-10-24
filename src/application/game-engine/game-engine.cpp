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

    Global::gameStateService->pushGameState(GameStateRoute::MAIN_MENU);

    while (!keyboardManager->exitEventIsCalled())
    {
      timeManager->updateTime();
      Global::gameStateService->renderCurrentState();
      renderer->updateScreen();
    }
  }

}
