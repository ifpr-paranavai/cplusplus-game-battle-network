#include "element.h"

namespace Game
{
    Element::Element(TimeManagerPort *_timeManager, int width, int height) : timeManager(_timeManager)
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