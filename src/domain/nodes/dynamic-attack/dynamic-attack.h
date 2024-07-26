#pragma once
#include "../collision-box/collision-box.h"
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../../utils/math/vector.h"
#include "../visual-element/visual-element.h"
#include "../../../config/config.h"
#include "../dynamic-body/dynamic-body.h"

namespace Game
{
    class DynamicAttack : public DynamicBody
    {
    protected:
        VisualElement sprite;
        bool deleted = false;
        int damage;

    public:
        DynamicAttack(Vector initialPosition);

        void update();
        void render();

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