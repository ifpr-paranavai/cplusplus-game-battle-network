#pragma once
#include <list>
#include "../collision-box/collision-box.h"
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../dto/vector/vector.h"
#include "../../../config/config.h"
#include "../dynamic-body/dynamic-body.h"
#include "../sprite/sprite.h"

namespace Game
{
    class DynamicAttack : public DynamicBody
    {
    protected:
        std::list<Sprite> sprites;
        bool deleted = false;
        int damage;

    public:
        DynamicAttack(Vector initialPosition);

        void update();
        virtual void render();

        bool isDeleted()
        {
            return this->deleted;
        }

        int getDamage()
        {
            return this->damage;
        }
    };
}