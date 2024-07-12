#pragma once
#include "../../nodes/character/character.h"

namespace Game
{
    class Enemy : public Character
    {
    protected:
        void onCollision(Element *other) override;

    public:
        Enemy(RendererPort *_renderer);
        void update() override;
    };
}