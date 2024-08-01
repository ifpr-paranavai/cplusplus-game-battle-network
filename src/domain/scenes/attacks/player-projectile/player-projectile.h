#pragma once
#include "../../../nodes/dynamic-attack/dynamic-attack.h"
#include "../../../../utils/math/vector.h"

namespace Game
{
    class PlayerProjectile : public DynamicAttack
    {
    protected:
        void onCollision(Element *other) override;

    public:
        PlayerProjectile(Vector initialPosition);
    };
}
