#pragma once
#include <iostream>
#include <list>
#include "../../../utils/math/vector.h"
#include "../collision-box/collision-box.h"

namespace Game
{
    class Element
    {
    protected:
        std::list<CollisionBox> collisionBoxes;
        int width = 0;
        int height = 0;
        Vector position;

        virtual void onCollision(Element *other) = 0;

    public:
        Element(int width, int height);

        virtual void update();
        virtual void checkCollision(Element *other);
        std::list<CollisionBox> getCollisionBoxes();
    };
}