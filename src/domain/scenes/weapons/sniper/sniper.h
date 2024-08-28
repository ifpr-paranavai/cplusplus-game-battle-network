#pragma once
#include "../../../nodes/weapon/weapon.h"
#include "../../attacks/projectile/projectile.h"

namespace Game
{
    class Sniper : public Weapon
    {
    private:
        const float spriteWidth = 160;
        const float spriteHeight = 40;
        const SoundEffect projectileSFX = Global::adaptersInstance.audioManager->initSoundEffect("assets/sounds/projectile.wav");

        AnimatedSprite idleSprite = AnimatedSprite({0,
                                                    "assets/sprites/weapons/sniper/idle",
                                                    1,
                                                    this->spriteWidth,
                                                    this->spriteHeight,
                                                    false,
                                                    Vector(0, 0)});
        AnimatedSprite shootAnimation = AnimatedSprite({0.01f,
                                                        "assets/sprites/weapons/sniper/shooting",
                                                        28,
                                                        200,
                                                        this->spriteHeight,
                                                        false,
                                                        Vector(0, 0)});
        bool canAttack = true;

    public:
        Sniper(const Vector relativePosition);

        void attack(const Vector initialPosition, const Vector elementTilePosition) override;

        void render(const Vector position) override
        {
            Weapon::render(position);
            this->idleSprite.renderSprite(position + this->relativePosition);
        }
    };
}