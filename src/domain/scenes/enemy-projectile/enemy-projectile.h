#pragma once
#include "../../nodes/projectile/projectile.h"

namespace Game
{
    class EnemyProjectile : public Projectile
    {
    protected:
        void onCollision(Element *other) override;

    public:
        EnemyProjectile(Vector initialPosition);
    };
}