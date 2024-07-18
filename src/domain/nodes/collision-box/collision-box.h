#pragma once
#include "../../../utils/math/vector.h"

namespace Game
{
    class CollisionBox
    {
    private:
        int width;
        int height;
        Vector position;

    public:
        CollisionBox(Vector position, int with, int height);
        void setPosition(Vector position);
        bool collidesWith(CollisionBox *other);
        Vector getPosition();
        int getWidth();
        int getHeight();
    };
}
