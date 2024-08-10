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
        AnimatedSprite idleSprite = AnimatedSprite({0.2f,
                                                    {"assets/sprites/enemies/fireman/idle/0.png",
                                                     "assets/sprites/enemies/fireman/idle/1.png",
                                                     "assets/sprites/enemies/fireman/idle/2.png",
                                                     "assets/sprites/enemies/fireman/idle/3.png",
                                                     "assets/sprites/enemies/fireman/idle/4.png"},
                                                    this->width,
                                                    this->height,
                                                    true,
                                                    Vector(0, 0)});
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