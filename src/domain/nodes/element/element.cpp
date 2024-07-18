#include "element.h"

namespace Game
{
    Element::Element(int width, int height)
    {
        this->width = width;
        this->height = height;
        this->collisionBox = new CollisionBox(this->position, width, height);
    }

    void Element::update()
    {
        this->collisionBox->setPosition(this->position);
    }

    CollisionBox *Element::getCollisionBox()
    {
        return this->collisionBox;
    }

    void Element::checkCollision(Element *element)
    {
        if (this->collisionBox->collidesWith(element->getCollisionBox()))
        {
            element->onCollision(element);
        }
    }
}