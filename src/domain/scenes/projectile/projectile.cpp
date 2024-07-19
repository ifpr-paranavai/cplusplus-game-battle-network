#include "projectile.h"

namespace Game
{
    Projectile::Projectile(
        Vector initialPosition) : Element(10, 10)
    {
        this->sprite.setConfig("#FFFF00", initialPosition, this->width, this->height);
        this->position = initialPosition;
        this->collisionBoxes.push_back(CollisionBox(this->position, this->width, this->height));
    }

    void Projectile::update()
    {
        const float deltaTime = Global::adaptersInstance.timeManager->getDeltaTime();
        this->position += this->velocity * deltaTime;
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