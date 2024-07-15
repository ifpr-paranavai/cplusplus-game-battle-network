#pragma once
#include <string>
#include <random>
#include <ctime>
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
        bool checkIsWithinTileLimits(int rowIndex, int columnIndex);
        Direction getRandomDirection();
        void moveRandomlyWithinLimits();

    protected:
        void onCollision(Element *other) override;

    public:
        Enemy(RendererPort *_renderer, TimeManagerPort *_timeManager);
        void update() override;
    };
}