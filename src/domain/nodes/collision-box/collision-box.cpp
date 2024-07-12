#include "collision-box.h"

namespace Game
{
    CollisionBox::CollisionBox(int positionX, int positionY, int with, int height)
    {
        this->positionX = positionX;
        this->positionY = positionY;
        this->width = with;
        this->height = height;
    }

    void CollisionBox::setPosition(int positionX, int positionY)
    {
        this->positionX = positionX;
        this->positionY = positionY;
    }

    int CollisionBox::getPositionX()
    {
        return this->positionX;
    }

    int CollisionBox::getPositionY()
    {
        return this->positionY;
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
        return (this->positionX < other->getPositionX() + other->getWidth() &&
                this->positionX + this->width > other->getPositionX() &&
                this->positionY < other->getPositionY() + other->getHeight() &&
                this->positionY + this->height > other->getPositionY());
    }
}