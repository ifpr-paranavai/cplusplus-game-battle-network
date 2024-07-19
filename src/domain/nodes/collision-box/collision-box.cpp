#include "collision-box.h"

namespace Game
{
    CollisionBox::CollisionBox(Vector position, int with, int height)
    {
        this->position = position;
        this->width = with;
        this->height = height;
    }

    void CollisionBox::setPosition(Vector position)
    {
        this->position = position;
    }

    Vector CollisionBox::getPosition()
    {
        return this->position;
    }

    int CollisionBox::getWidth()
    {
        return this->width;
    }

    int CollisionBox::getHeight()
    {
        return this->height;
    }

    bool CollisionBox::collidesWith(CollisionBox &other)
    {
        Vector otherPosition = other.getPosition();

        return (this->position.x < otherPosition.x + other.getWidth() &&
                this->position.x + width > otherPosition.x &&
                this->position.y < otherPosition.y + other.getHeight() &&
                this->position.y + height > otherPosition.y);
    }
}