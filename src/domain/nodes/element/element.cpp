#include "element.h"

namespace Game
{
    Element::Element(int width, int height)
    {
        this->collisionBox = new CollisionBox(this->positionX, this->positionY, width, height);
    }

    void Element::update()
    {
        this->collisionBox->setPosition(this->positionX, this->positionY);
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