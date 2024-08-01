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