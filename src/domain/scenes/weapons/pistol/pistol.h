#pragma once
#include <iostream>
#include "../../../nodes/weapon/weapon.h"
#include "../../../nodes/animated-sprited/animated-sprited.h"
#include "../../attacks/projectile/projectile.h"

namespace Game
{
    class Pistol : public Weapon
    {
    private:
        const float spriteWidth = 100;
        const float spriteHeight = 60;
        const SoundEffect projectileSFX = Global::adaptersInstance.audioManager->initSoundEffect("assets/sounds/projectile.wav");
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
        bool canAttack = true;

    public:
        Pistol(const Vector relativePosition);

        void attack(const Vector initialPosition, const Vector elementTilePosition) override;
    };
}