#pragma once
#include "../../ports/keyboard-manager/keyboard-manager.h"
#include "../../ports/time-manager/time-manager.h"
#include "../../ports/renderer/renderer.h"
#include "../../ports/window-manager/window-manager.h"
#include "../../ports/audio-manager/audio-manager.h"
#include "../../ports/text-renderer/text-renderer.h"

namespace Game
{

    namespace Global
    {
        struct Adapters
        {
            KeyboardManagerPort *keyboardManager = nullptr;
            TimeManagerPort *timeManager = nullptr;
            RendererPort *renderer = nullptr;
            WindowManagerPort *windowManager = nullptr;
            AudioManagerPort *audioManager = nullptr;
            TextRendererPort *textRenderer = nullptr;

            Adapters()
            {
            }
        };

        extern Adapters adaptersInstance;
    }

}