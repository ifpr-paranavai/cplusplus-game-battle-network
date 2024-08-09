#pragma once
#include "../../../nodes/dynamic-attack/dynamic-attack.h"
#include "../../../dto/vector/vector.h"
#include "../../../dto/sound-effect/sound-effect.h"

namespace Game
{
    class PlayerProjectile : public DynamicAttack
    {
    private:
        const SoundEffect projectileSFX = Global::adaptersInstance.audioManager->initSoundEffect("assets/sounds/player-projectile.wav");

    protected:
        void onCollision(Element *other) override;

    public:
        PlayerProjectile(Vector initialPosition);
    };
}
