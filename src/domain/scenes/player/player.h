#pragma once
#include <iostream>
#include <ctime>
#include "../../../utils/global/global.h"
#include "../../nodes/character/character.h"
#include "../../../ports/keyboard-manager/keyboard-manager.h"
#include "../projectile/projectile.h"

namespace Game
{
    class Player : public Character
    {
    private:
        bool movementKeyAlreadyPressed = false;
        bool attackKeyAlreadyPressed = false;
        std::list<Projectile *> projectiles;

        void handleMovement();
        void handleAttack();
        void attack();
        void checkProjectiles();

    public:
        Player();
        void update() override;
        void onCollision(Element *other) override;
        std::list<Projectile *> getProjectiles();
    };
}