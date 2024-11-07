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

        inline void setPosition(const Vector position) { this->position = position; }
        inline const Vector &getPosition() const { return this->position; }
        inline int getWidth() const { return this->width; }
        inline int getHeight() const { return this->height; }

        bool collidesWith(const CollisionBox &other);
        void renderCollisionBox() const;
    };
}
