#pragma once
#include <iostream>
#include "../../nodes/character/character.h"
#include "../../../ports/event-manager/event-manager.h"

namespace Game
{
    class Player : public Character
    {
    private:
        bool keyAlreadyPressed = false;
        EventManagerPort *eventManager;

    public:
        Player(RendererPort *_renderer, EventManagerPort *_eventManager);
        void update() override;
    };
}