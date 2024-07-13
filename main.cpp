#include <iostream>

#include "src/application/game-engine/game-engine.h"
#include "src/adapters/sdl/keyboard-manager/keyboard-manager.h"
#include "src/adapters/sdl/window-manager/window-manager.h"
#include "src/adapters/sdl/renderer/renderer.h"
#include "src/adapters/sdl/time-manager/time-manager.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

int main(int argc, char *argv[])
{
    Game::SDLWindowManagerAdapter *windowManager = new Game::SDLWindowManagerAdapter();
    Game::SDLKeyboardManagerAdapter *eventManager = new Game::SDLKeyboardManagerAdapter();
    Game::SDLRendererAdapter *renderer = new Game::SDLRendererAdapter(windowManager);
    Game::SDLTimeManagerAdapter *timeManager = new Game::SDLTimeManagerAdapter();
    Game::GameEngine *gameEngine = new Game::GameEngine(windowManager, eventManager, renderer, timeManager);
    gameEngine->startGame();
    return EXIT_SUCCESS;
}
