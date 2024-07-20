#include <iostream>

#include "src/application/game-engine/game-engine.h"
#include "src/utils/global-adapters/global-adapters.h"
#include "src/adapters/sdl/keyboard-manager/keyboard-manager.h"
#include "src/adapters/sdl/window-manager/window-manager.h"
#include "src/adapters/sdl/renderer/renderer.h"
#include "src/adapters/sdl/time-manager/time-manager.h"

int main(int argc, char *argv[])
{
    Game::Global::adaptersInstance.windowManager = new Game::SDLWindowManagerAdapter();
    Game::Global::adaptersInstance.renderer = new Game::SDLRendererAdapter();
    Game::Global::adaptersInstance.keyboardManager = new Game::SDLKeyboardManagerAdapter();
    Game::Global::adaptersInstance.timeManager = new Game::SDLTimeManagerAdapter();

    Game::GameEngine gameEngine;
    gameEngine.startGame();
    return EXIT_SUCCESS;
}
