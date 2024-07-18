#pragma once
#include <iostream>
#include "../../../utils/math/vector.h"
#include "../collision-box/collision-box.h"
#include "../../../ports/time-manager/time-manager.h"

namespace Game
{
    class Element
    {
    protected:
        CollisionBox *collisionBox;
        TimeManagerPort *timeManager;
        int width = 0;
        int height = 0;
        Vector position;

        virtual void onCollision(Element *other) = 0;

    public:
        Element(TimeManagerPort *_timeManager, int width, int height);

        virtual void update();
        virtual void checkCollision(Element *other);
        CollisionBox *getCollisionBox();
    };
}