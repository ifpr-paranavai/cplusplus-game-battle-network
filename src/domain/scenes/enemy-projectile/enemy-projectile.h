#pragma once
#include "../../nodes/dynamic-attack/dynamic-attack.h"

namespace Game
{
    class EnemyProjectile : public DynamicAttack
    {
    protected:
        void onCollision(Element *other) override;

    public:
        EnemyProjectile(Vector initialPosition);
    };
}