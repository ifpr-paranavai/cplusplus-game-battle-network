#pragma once
#include <memory>
#include "../../ports/window-manager/window-manager.h"
#include "../../ports/event-manager/event-manager.h"
#include "../../ports/renderer/renderer.h"
#include "../../domain/scenes/player/player.h"
#include "../../domain/scenes/arena/arena.h"
#include "../../config/config.h"

namespace Game
{
    class GameEngine
    {
    private:
        WindowManagerPort *windowManager;
        EventManagerPort *eventManager;
        RendererPort *renderer;

    public:
        GameEngine(WindowManagerPort *_windowManager, EventManagerPort *_eventManager, RendererPort *_renderer);
        void startGame();
    };
}