#pragma once
#include <string>
#include <list>
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../dto/vector/vector.h"
#include "../tile-based-body/tile-based-body.h"
#include "../sprite/sprite.h"

namespace Game
{
    class Character : public TileBasedBody
    {
    protected:
        int life = 100;
        std::list<Sprite> sprites;

    public:
        Character(
            int width,
            int height);

        virtual void render();

        int getWidth()
        {
            return this->width;
        }

        int getHeight()
        {
            return this->height;
        }

        int getLife()
        {
            return this->life;
        }

        virtual ~Character() = default;
    };
}