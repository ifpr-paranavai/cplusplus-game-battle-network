#pragma once
#include "../../nodes/sprite/sprite.h"
#include "../../nodes/tile-based-attack/tile-based-attack.h"

namespace Game
{
    class Flame : public TileBasedBody
    {
    private:
        const Sprite sprite;

    protected:
        void onCollision(Element *other) {};

    public:
        Flame(Vector tilePosition);

        void renderSprite() const
        {
            this->sprite.renderSprite(this->position);
        }
    };
}