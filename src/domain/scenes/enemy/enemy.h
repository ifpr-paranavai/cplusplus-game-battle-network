#pragma once
#include "../../nodes/character/character.h"

namespace Game
{
    class Enemy : public Character
    {
    public:
        Enemy(RendererPort *_renderer);
        void update() override;
    };
}