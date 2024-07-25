#pragma once
#include "../../nodes/projectile/projectile.h"
#include "../../../utils/math/vector.h"

namespace Game
{
    class PlayerProjectile : public Projectile
    {
    protected:
        void onCollision(Element *other) override;

    public:
        PlayerProjectile(Vector initialPosition);
    };
}
