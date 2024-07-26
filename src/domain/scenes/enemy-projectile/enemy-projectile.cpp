#include "enemy-projectile.h"
#include "../enemy/enemy.h"

namespace Game
{
    EnemyProjectile::EnemyProjectile(Vector initialPosition) : DynamicAttack(initialPosition)
    {
        this->velocity = {-1000, 0};
        this->damage = 10;
        this->sprite.setConfig("#FF0000", initialPosition, this->width, this->height);
    }

    void EnemyProjectile::onCollision(Element *other)
    {
        if (dynamic_cast<Enemy *>(other) || dynamic_cast<EnemyProjectile *>(other))
        {
            return;
        }

        this->deleted = true;
    }
}