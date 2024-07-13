#include "game-engine.h"

namespace Game
{

    GameEngine::GameEngine(
        WindowManagerPort *_windowManager,
        KeyboardManagerPort *_eventManager,
        RendererPort *_renderer,
        TimeManagerPort *_timeManager) : windowManager(_windowManager),
                                         eventManager(_eventManager),
                                         renderer(_renderer),
                                         timeManager(_timeManager)
    {
    }

    void GameEngine::startGame()
    {
        LogManager::log("Starting game...");
        this->windowManager->createWindow(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT);
        LogManager::log("Window created");
        std::unique_ptr<Player> player = std::make_unique<Player>(this->renderer, this->eventManager, this->timeManager);
        LogManager::log("Player created");
        std::unique_ptr<Arena> arena = std::make_unique<Arena>(this->renderer, this->timeManager);
        LogManager::log("Arena created");
        arena->setPlayer(player.get());
        LogManager::log("Game started");

        while (!this->eventManager->exitEventIsCalled())
        {
            LogManager::log("Updating game...");
            this->timeManager->updateTime();
            LogManager::log("Time Manager updated");
            arena->render();
            LogManager::log("Arena rendered");
        }

        this->renderer->destroyRenderer();
        this->windowManager->destroyWindow();
    }

}
