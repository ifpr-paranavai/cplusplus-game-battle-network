#pragma once
#include "../../nodes/collision-box/collision-box.h"
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../../utils/math/vector.h"
#include "../../nodes/visual-element/visual-element.h"
#include "../../../config/config.h"
#include "../../nodes/dynamic-body/dynamic-body.h"

namespace Game
{
    class Projectile : public DynamicBody
    {
    private:
        VisualElement sprite;
        bool deleted = false;

        void onCollision(Element *other);

    public:
        Projectile(Vector initialPosition);

        void update();
        void render();
        bool isDeleted();
    };
}