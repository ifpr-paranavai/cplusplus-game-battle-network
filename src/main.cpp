#include <iostream>

#include "application/game-engine/game-engine.h"
#include "utils/global-adapters/global-adapters.h"
#include "adapters/sdl/keyboard-manager/keyboard-manager.h"
#include "adapters/sdl/window-manager/window-manager.h"
#include "adapters/sdl/renderer/renderer.h"
#include "adapters/sdl/time-manager/time-manager.h"
#include "adapters/sdl/audio-manager/audio-manager.h"

int main(int argc, char *argv[])
{
    Game::Global::adaptersInstance.windowManager = new Game::SDLWindowManagerAdapter();
    Game::Global::adaptersInstance.renderer = new Game::SDLRendererAdapter();
    Game::Global::adaptersInstance.keyboardManager = new Game::SDLKeyboardManagerAdapter();
    Game::Global::adaptersInstance.timeManager = new Game::SDLTimeManagerAdapter();
    Game::Global::adaptersInstance.audioManager = new Game::SDLAudioManagerAdapter();

    Game::GameEngine gameEngine;
    gameEngine.startGame();
    return EXIT_SUCCESS;
}
