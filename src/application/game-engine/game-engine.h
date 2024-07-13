#pragma once
#include <memory>
#include "../../ports/window-manager/window-manager.h"
#include "../../ports/keyboard-manager/keyboard-manager.h"
#include "../../ports/renderer/renderer.h"
#include "../../ports/time-manager/time-manager.h"
#include "../../domain/scenes/player/player.h"
#include "../../domain/scenes/arena/arena.h"
#include "../../config/config.h"
#include "../../utils/log-manager/log-manager.h"

namespace Game
{
    class GameEngine
    {
    private:
        WindowManagerPort *windowManager;
        KeyboardManagerPort *eventManager;
        RendererPort *renderer;
        TimeManagerPort *timeManager;

    public:
        GameEngine(
            WindowManagerPort *_windowManager,
            KeyboardManagerPort *_eventManager,
            RendererPort *_renderer,
            TimeManagerPort *_timeManager);
        void startGame();
    };
}