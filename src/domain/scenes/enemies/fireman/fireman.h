#pragma once
#include "../../enemy/enemy.h"
#include "../../flamethrower/flamethrower.h"
#include "../../../global/global-services/global-services.h"

namespace Game
{
    enum class Attacks
    {
        FLAMETHROWER,
        BOMB
    };

    class FiremanEnemy : public Enemy
    {
    private:
        float attackDelayTime = 0;
        float attackDelayTimer = 0;
        void flamethrowerAttack();
        void bombAttack();

    protected:
        void attack() override;

    public:
        FiremanEnemy();

        void update() override;
    };
}