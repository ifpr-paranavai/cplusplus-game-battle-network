#include "stab.h"

namespace Game
{
    Stab::Stab(const Vector _swordTilePosition, const int damage) : TileBasedAttack()
    {
        this->width = 60;
        this->height = 80;
        this->damage = damage;
        this->setTilePosition(_swordTilePosition + Vector{1, 0});
        this->collisionBoxes.emplace_back(this->position, this->width, this->height);
    }

}