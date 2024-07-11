#include <iostream>

#include "src/application/game-engine/game-engine.h"
#include "src/adapters/sdl/event-manager/event-manager.h"
#include "src/adapters/sdl/window-manager/window-manager.h"
#include "src/adapters/sdl/renderer/renderer.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

int main(int argc, char *argv[])
{
    Game::SDLWindowManagerAdapter *windowManager = new Game::SDLWindowManagerAdapter();
    Game::SDLEventManagerAdapter *eventManager = new Game::SDLEventManagerAdapter();
    Game::SDLRendererAdapter *renderer = new Game::SDLRendererAdapter(windowManager);
    Game::GameEngine *gameEngine = new Game::GameEngine(windowManager, eventManager, renderer);
    gameEngine->startGame();
    return EXIT_SUCCESS;
}
