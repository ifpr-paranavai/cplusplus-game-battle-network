#pragma once
#include "../../../nodes/dynamic-attack/dynamic-attack.h"
#include "../../../dto/vector/vector.h"
#include "../../../dto/sound-effect/sound-effect.h"

namespace Game
{
    class Projectile : public DynamicAttack
    {
    protected:
        void onCollision(GameObject *other) override;

    public:
        Projectile(const Vector initialPosition, const int damage);
    };
}
