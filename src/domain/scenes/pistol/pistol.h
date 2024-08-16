#pragma once
#include <iostream>
#include "../../nodes/animated-sprited/animated-sprited.h"
#include "../../global/global-services/global-services.h"
#include "../../nodes/element/element.h"
#include "../../dto/vector/vector.h"
#include "../attacks/player-projectile/player-projectile.h"

namespace Game
{
    class Pistol
    {
    private:
        const Vector relativePosition;
        const float spriteWidth = 100;
        const float spriteHeight = 60;
        AnimatedSprite idleAnimation = AnimatedSprite({0,
                                                       "assets/sprites/weapons/pistol/idle",
                                                       1,
                                                       this->spriteWidth,
                                                       this->spriteHeight,
                                                       false,
                                                       Vector(0, 0)});
        AnimatedSprite shootAnimation = AnimatedSprite({0.025f,
                                                        "assets/sprites/weapons/pistol/shooting",
                                                        11,
                                                        this->spriteWidth,
                                                        this->spriteHeight,
                                                        false,
                                                        Vector(0, 0)});
        AnimatedSprite *currentAnimation = nullptr;

        void updateCurrentAnimation(AnimatedSprite *newAnimation);

    public:
        Pistol(Vector relativePosition);

        void attack();

        void render(Vector position)
        {
            this->currentAnimation->renderSprite(position + this->relativePosition);
        }
    };
}