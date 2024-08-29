#pragma once
#include <iostream>
#include "../../../nodes/weapon/weapon.h"
#include "../../../nodes/animated-sprited/animated-sprited.h"
#include "../../attacks/projectile/projectile.h"
#include "../../../../utils/observer/observer.h"

namespace Game
{
    class Pistol : public Weapon
    {
    private:
        const float spriteWidth = 100;
        const float spriteHeight = 60;
        const SoundEffect projectileSFX = Global::adaptersInstance.audioManager->initSoundEffect("assets/sounds/projectile.wav");
        AnimatedSprite shootAnimation = AnimatedSprite({0.025f,
                                                        "assets/sprites/weapons/pistol/shooting",
                                                        11,
                                                        this->spriteWidth,
                                                        this->spriteHeight,
                                                        false,
                                                        Vector(0, 0)});

    public:
        Pistol(const Vector relativePosition);

        void attack(const Vector initialPosition, const Vector elementTilePosition) override;
    };
}