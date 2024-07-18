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

    bool CollisionBox::collidesWith(CollisionBox *other)
    {
        Vector otherPosition = other->getPosition();

        return (position[0] < otherPosition[0] + other->getWidth() &&
                position[0] + width > otherPosition[0] &&
                position[1] < otherPosition[1] + other->getHeight() &&
                position[1] + height > otherPosition[1]);
    }
}