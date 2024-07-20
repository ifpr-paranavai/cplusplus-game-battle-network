#pragma once
#include <string>
#include <random>
#include <ctime>
#include "../../../utils/global/global.h"
#include "../../nodes/character/character.h"
#include "../../../utils/log-manager/log-manager.h"

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
        float decisionTime = 1;
        float decisionTimer = 0;
        bool dead = false;

        void handleMovement();
        bool tryMove(Direction direction);
        Direction getRandomDirection();
        void moveRandomlyWithinLimits();

    protected:
        void onCollision(Element *other) override;

    public:
        Enemy();
        void update() override;
    };
}