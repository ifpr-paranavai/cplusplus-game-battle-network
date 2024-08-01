#include "player-projectile.h"
#include "../../player/player.h"

namespace Game
{
    PlayerProjectile::PlayerProjectile(Vector initialPosition) : DynamicAttack(initialPosition)
    {
        this->velocity = {1000, 0};
        this->damage = 1;
        this->sprite.setConfig("#FFFF00", initialPosition, this->width, this->height);
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
