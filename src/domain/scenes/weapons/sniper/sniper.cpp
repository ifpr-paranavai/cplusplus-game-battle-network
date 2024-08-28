#include "sniper.h"

namespace Game
{
    Sniper::Sniper(const Vector relativePosition) : Weapon(relativePosition, 25)
    {
        this->shootAnimation.addOnAnimationEndCallback(
            [this]()
            {
                this->canAttack = true;
                this->queueAnimationChange(&this->idleSprite);
            });
    }

    void Sniper::attack(const Vector elementPosition, const Vector elementTilePosition)
    {
        if (!this->canAttack)
        {
            return;
        }
        this->canAttack = false;
        const Vector absolutePosition = elementPosition + this->relativePosition;
        const Vector projectilePosition(absolutePosition.x + this->spriteWidth, absolutePosition.y);
        std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(projectilePosition, this->damage);
        Global::attacksService->addDynamicAttack(std::move(projectile));
        this->queueAnimationChange(&this->shootAnimation);
        Global::adaptersInstance.audioManager->playWavSoundEffect(this->projectileSFX);
    }
}