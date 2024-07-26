#pragma once
#include "../tile-based-body/tile-based-body.h"

namespace Game
{
    class TileBasedAttack : public TileBasedBody
    {
    protected:
        int damage;
        bool deleted = false;

    public:
        TileBasedAttack(int width, int height) : TileBasedBody(width, height) {}

        virtual void render() = 0;

        int getDamage()
        {
            return this->damage;
        }

        bool isDeleted()
        {
            return this->deleted;
        }
    };
}