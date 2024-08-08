#include "player-projectile.h"
#include "../../player/player.h"

namespace Game
{
    PlayerProjectile::PlayerProjectile(Vector initialPosition) : DynamicAttack(initialPosition)
    {
        this->sprite.setSpritePath("assets/sprites/attacks/projectile/0.png");
        this->velocity = {1000, 0};
        this->damage = 1;
        this->width = 30.5;
        this->height = 29.75;
        this->sprite.setConfig("#FFFF00", initialPosition, this->width, this->height);
        Global::adaptersInstance.audioManager->playWavSoundEffect("assets/sounds/player-projectile.wav");
    }

    void PlayerProjectile::onCollision(Element *other)
    {
        if (dynamic_cast<Player *>(other) || dynamic_cast<PlayerProjectile *>(other))
        {
            return;
        }

        this->deleted = true;
    }
}
