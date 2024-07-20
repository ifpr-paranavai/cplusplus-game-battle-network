#include "projectile.h"

namespace Game
{
    Projectile::Projectile(
        Vector initialPosition) : DynamicBody(10, 10)
    {
        this->velocity = {1000, 0};
        this->sprite.setConfig("#FFFF00", initialPosition, this->width, this->height);
        this->position = initialPosition;
        this->collisionBoxes.push_back(CollisionBox(this->position, this->width, this->height));
    }

    void Projectile::update()
    {
        this->move();
        this->sprite.setPosition(this->position);
        if (this->position.x > Config::WINDOW_WIDTH)
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

    void Projectile::onCollision(Element *other)
    {
        this->deleted = true;
    }

    bool Projectile::isDeleted()
    {
        return this->deleted;
    }
}