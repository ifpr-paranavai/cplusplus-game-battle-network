#pragma once
#include "../../dto/vector/vector.h"
#include "../../../config/config.h"
#include "../../../utils/global-adapters/global-adapters.h"

namespace Game
{
    class CollisionBox
    {
    private:
        int width;
        int height;
        Vector position;

    public:
        CollisionBox(const Vector position, const int with, const int height);
        void setPosition(const Vector position);
        bool collidesWith(const CollisionBox &other);

        Vector getPosition() const
        {
            return this->position;
        }

        int getWidth() const
        {
            return this->width;
        }

        int getHeight() const
        {
            return this->height;
        }

        void renderCollisionBox() const;
    };
}
