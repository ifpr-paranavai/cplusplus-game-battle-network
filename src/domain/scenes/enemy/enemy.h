#pragma once
#include <string>
#include <random>
#include <ctime>
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../nodes/character/character.h"
#include "../../../utils/log-manager/log-manager.h"
#include "../attacks/enemy-projectile/enemy-projectile.h"
#include "../../global/global-services/global-services.h"

namespace Game
{
    enum class Direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    class Enemy : public Character
    {
    private:
        float movementDecisionTimer = 0;
        float attackTimer = 0;
        bool dead = false;

        void handleMovement();
        void handleAttack();
        bool tryMove(Direction direction);
        Direction getRandomDirection();
        void moveRandomlyWithinLimits();

    protected:
        float movementDecisionTime = 1;
        float attackTime = 1;
        bool canMove = true;
        bool canAttack = true;

        virtual void attack() = 0;
        void onCollision(Element *other) override;

    public:
        Enemy();
        void update() override;
    };
}