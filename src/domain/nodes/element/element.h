#pragma once
#include <iostream>
#include "../../../utils/math/vector.h"
#include "../collision-box/collision-box.h"

namespace Game
{
    class Element
    {
    protected:
        CollisionBox *collisionBox;
        int width = 0;
        int height = 0;
        Vector position;

        virtual void onCollision(Element *other) = 0;

    public:
        Element(int width, int height);

        virtual void update();
        virtual void checkCollision(Element *other);
        CollisionBox *getCollisionBox();
    };
}