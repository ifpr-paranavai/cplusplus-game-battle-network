#pragma once
#include <iostream>
#include <ctime>
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../nodes/character/character.h"
#include "../../../ports/keyboard-manager/keyboard-manager.h"
#include "../player-projectile/player-projectile.h"
#include "../../../utils/log-manager/log-manager.h"
#include "../../global/global-services/global-services.h"

namespace Game
{
    class Player : public Character
    {
    private:
        bool movementKeyAlreadyPressed = false;
        bool attackKeyAlreadyPressed = false;

        void handleMovement();
        void handleAttack();
        void attack();

    public:
        Player();
        void update() override;
        void onCollision(Element *other) override;
    };
}