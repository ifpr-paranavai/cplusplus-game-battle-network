#include "element.h"

namespace Game
{
    Element::Element(int width, int height)
    {
        this->width = width;
        this->height = height;
    }

    void Element::update()
    {
    }

    std::list<CollisionBox> Element::getCollisionBoxes()
    {
        return this->collisionBoxes;
    }

    void Element::checkCollision(Element *element)
    {
        if (!element)
        {
            throw std::invalid_argument("element is null");
        }

        for (auto &collisionBox : this->collisionBoxes)
        {
            for (auto &collisionBox2 : element->getCollisionBoxes())
            {
                if (collisionBox.collidesWith(collisionBox2))
                {
                    this->onCollision(element);
                }
            }
        }
    }

}