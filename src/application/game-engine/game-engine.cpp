#include "game-engine.h"

namespace Game
{

    GameEngine::GameEngine(
        WindowManagerPort *_windowManager,
        EventManagerPort *_eventManager,
        RendererPort *_renderer) : windowManager(_windowManager),
                                   eventManager(_eventManager),
                                   renderer(_renderer)
    {
    }

    void GameEngine::startGame()
    {
        this->windowManager->createWindow(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT);

        std::unique_ptr<Player> player = std::make_unique<Player>(this->renderer, this->eventManager);
        std::unique_ptr<Arena> arena = std::make_unique<Arena>(this->renderer);
        arena->setPlayer(player.get()); // Ajuste necessário se setPlayer() requer um ponteiro cru

        while (!this->eventManager->exitEventIsCalled())
        {
            arena->render();
        }

        this->windowManager->destroyWindow();
    }

}
