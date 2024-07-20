#pragma once
#include "../../ports/keyboard-manager/keyboard-manager.h"
#include "../../ports/time-manager/time-manager.h"
#include "../../ports/renderer/renderer.h"
#include "../../ports/window-manager/window-manager.h"
#include "../../domain/services/projectiles-service/projectiles-service.h"
namespace Game
{

    namespace Global
    {
        struct Adapters
        {
            KeyboardManagerPort *keyboardManager;
            TimeManagerPort *timeManager;
            RendererPort *renderer;
            WindowManagerPort *windowManager;

            Adapters() : windowManager(nullptr),
                         renderer(nullptr),
                         keyboardManager(nullptr),
                         timeManager(nullptr)
            {
            }
        };

        extern Adapters adaptersInstance;
    }

}