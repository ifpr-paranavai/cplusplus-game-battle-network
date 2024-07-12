#pragma once
#include <iostream>
#include "../collision-box/collision-box.h"

namespace Game
{
    class Element
    {
    protected:
        CollisionBox *collisionBox;
        int width = 0;
        int height = 0;
        int positionX = 0;
        int positionY = 0;

        virtual void onCollision(Element *other) = 0;

    public:
        Element(int width, int height);

        virtual void update();
        virtual void checkCollision(Element *other);
        CollisionBox *getCollisionBox();
    };
}