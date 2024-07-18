#include "game-engine.h"

namespace Game
{

    void GameEngine::startGame()
    {
        LogManager::log("Starting game...");
        Global::adaptersInstance.windowManager->createWindow(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT);
        LogManager::log("Window created");
        std::unique_ptr<Player> player = std::make_unique<Player>();
        LogManager::log("Player created");
        std::unique_ptr<Arena> arena = std::make_unique<Arena>();
        LogManager::log("Arena created");
        arena->setPlayer(player.get());
        LogManager::log("Game started");

        while (!Global::adaptersInstance.keyboardManager->exitEventIsCalled())
        {
            LogManager::log("Updating game...");
            Global::adaptersInstance.timeManager->updateTime();
            LogManager::log("Time Manager updated");
            arena->render();
            LogManager::log("Arena rendered");
        }

        Global::adaptersInstance.renderer->destroyRenderer();
        Global::adaptersInstance.windowManager->destroyWindow();
    }

}
