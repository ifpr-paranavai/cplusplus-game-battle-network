#include <iostream>

#include "application/game-engine/game-engine.h"
#include "utils/global-adapters/global-adapters.h"
#include "adapters/sdl/keyboard-manager/keyboard-manager.h"
#include "adapters/sdl/window-manager/window-manager.h"
#include "adapters/sdl/renderer/renderer.h"
#include "adapters/sdl/time-manager/time-manager.h"
#include "adapters/sdl/audio-manager/audio-manager.h"
#include "adapters/sdl/text-renderer/text-renderer.h"
#include "domain/global/global-services/global-services.h"
#include "./domain/services/game-state-service/game-state-service.h"

int main(int argc, char *argv[])
{
  Game::Global::adaptersInstance.windowManager = new Game::SDLWindowManagerAdapter();
  Game::Global::adaptersInstance.renderer = new Game::SDLRendererAdapter();
  Game::Global::adaptersInstance.keyboardManager = new Game::SDLKeyboardManagerAdapter();
  Game::Global::adaptersInstance.timeManager = new Game::SDLTimeManagerAdapter();
  Game::Global::adaptersInstance.audioManager = new Game::SDLAudioManagerAdapter();
  Game::Global::adaptersInstance.textRenderer = new Game::SDLTextRendererAdapter();
  Game::Global::initializeGlobalServices();
  Game::Global::gameStateService = new Game::GameStateService();

  Game::GameEngine gameEngine;
  gameEngine.startGame();

  delete Game::Global::adaptersInstance.windowManager;
  delete Game::Global::adaptersInstance.renderer;
  delete Game::Global::adaptersInstance.keyboardManager;
  delete Game::Global::adaptersInstance.timeManager;
  delete Game::Global::adaptersInstance.audioManager;
  delete Game::Global::adaptersInstance.textRenderer;
  Game::Global::cleanupGlobalServices();

  return EXIT_SUCCESS;
}
