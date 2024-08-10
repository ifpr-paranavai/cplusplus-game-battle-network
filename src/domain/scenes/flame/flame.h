#pragma once
#include "../../nodes/tile-based-attack/tile-based-attack.h"
#include "../../nodes/animated-sprited/animated-sprited.h"
#include "../../global/global-services/global-services.h"

namespace Game
{
    class Flame : public TileBasedBody
    {
    private:
        AnimatedSprite animatedSprite;

    protected:
        void onCollision(Element *other) {};

    public:
        Flame(Vector tilePosition);

        void renderSprite() const
        {
            this->animatedSprite.renderSprite(this->position);
        }
    };
}