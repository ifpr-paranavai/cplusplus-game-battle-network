#pragma once
#include <memory>
#include "../../utils/global-adapters/global-adapters.h"
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

    public:
        void startGame();
    };
}