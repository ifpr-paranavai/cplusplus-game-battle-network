#pragma once
#include <iostream>
#include <ctime>
#include "../../nodes/character/character.h"
#include "../../../ports/event-manager/event-manager.h"
#include "../projectile/projectile.h"

namespace Game
{
    class Player : public Character
    {
    private:
        bool movementKeyAlreadyPressed = false;
        bool attackKeyAlreadyPressed = false;
        EventManagerPort *eventManager;
        std::list<Projectile *> projectiles;

        void handleMovement();
        void handleAttack();
        void attack();
        void checkProjectiles();

    public:
        Player(RendererPort *_renderer, EventManagerPort *_eventManager);
        void update() override;
        void onCollision(Element *other) override;
        std::list<Projectile *> getProjectiles();
    };
}