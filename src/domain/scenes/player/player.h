#pragma once
#include <iostream>
#include <ctime>
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../nodes/character/character.h"
#include "../../../ports/keyboard-manager/keyboard-manager.h"
#include "../attacks/player-projectile/player-projectile.h"
#include "../../../utils/log-manager/log-manager.h"
#include "../../global/global-services/global-services.h"
#include "../../nodes/tile-based-attack/tile-based-attack.h"

namespace Game
{
    class Player : public Character
    {
    private:
        AnimatedSprite idleSprite = AnimatedSprite({0.2f,
                                                    {"assets/sprites/player/idle/0.png",
                                                     "assets/sprites/player/idle/1.png",
                                                     "assets/sprites/player/idle/2.png",
                                                     "assets/sprites/player/idle/3.png",
                                                     "assets/sprites/player/idle/4.png"},
                                                    this->width,
                                                    this->height,
                                                    false,
                                                    Vector(0, 0)});
        bool movementKeyAlreadyPressed = false;
        bool attackKeyAlreadyPressed = false;
        bool invencible = false;
        float invencibleTimer = 0;
        float invencibleTime = 1;

        void handleMovement();
        void handleAttack();
        void attack();
        void checkInvincibility();

    public:
        Player();
        void update() override;
        void onCollision(Element *other) override;
    };
}