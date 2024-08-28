#pragma once
#include <iostream>
#include "../../../nodes/weapon/weapon.h"
#include "../../../nodes/collision-box/collision-box.h"
#include "../../attacks/stab/stab.h"

namespace Game
{
    class Sword : public Weapon
    {
    private:
        AnimatedSprite idleAnimation = AnimatedSprite({
            0,
            "assets/sprites/weapons/sword/idle",
            1,
            102,
            20,
            false,
            Vector(0, 0),
        });
        AnimatedSprite stabAnimation = AnimatedSprite({
            0.1f,
            "assets/sprites/weapons/sword/stab",
            8,
            102,
            20,
            false,
            Vector(0, 0),
        });
        std::list<std::unique_ptr<TileBasedAttack>>::iterator stabAttackIt;
        bool canAttack = true;

    public:
        Sword(const Vector relativePosition);

        void attack(const Vector initialPosition, const Vector elementTilePosition) override;
    };
}
