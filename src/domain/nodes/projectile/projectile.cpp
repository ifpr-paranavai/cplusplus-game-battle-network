#include "projectile.h"

namespace Game
{
    Projectile::Projectile(
        Vector initialPosition) : DynamicBody(10, 10)
    {
        this->velocity = {1000, 0};
        this->position = initialPosition;
        this->collisionBoxes.push_back(CollisionBox(this->position, this->width, this->height));
    }

    void Projectile::update()
    {
        this->sprite.setPosition(this->position);
        if (this->position.x > Config::WINDOW_WIDTH || this->position.x < 0)
        {
            this->deleted = true;
        }
        for (CollisionBox &collisionBox : this->collisionBoxes)
        {
            collisionBox.setPosition(this->position);
        }
    }

    void Projectile::render()
    {
        this->sprite.renderSprite();
    }

}