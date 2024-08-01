#pragma once
#include "../../enemy/enemy.h"
#include "../../attacks/flamethrower-attack/flamethrower-attack.h"
#include "../../../global/global-services/global-services.h"
#include "../../attacks/bomb-attack/bomb-attack.h"

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
        void onCollision(Element *other) override;

    public:
        FiremanEnemy();

        void update() override;
    };
}