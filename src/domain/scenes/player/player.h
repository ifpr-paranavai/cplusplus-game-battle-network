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
#include "../pistol/pistol.h"

namespace Game
{
    class Player : public Character
    {
    private:
        AnimatedSprite idleSprite = AnimatedSprite({0.1f,
                                                    "assets/sprites/player/idle",
                                                    8,
                                                    120,
                                                    120,
                                                    false,
                                                    Vector(-((120 - this->width) / 2), -((120 - this->height) / 2))});
        Pistol pistol = Pistol({39, 28});
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
        void render() override;
    };
}