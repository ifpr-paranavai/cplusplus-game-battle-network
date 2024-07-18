#pragma once
#include "../../../utils/global/global.h"
#include "../../../utils/math/vector.h"
#include "../../nodes/visual-element/visual-element.h"
#include "../../nodes/element/element.h"
#include "../../../config/config.h"

namespace Game
{
    class Projectile : public Element
    {
    private:
        VisualElement sprite;
        Vector velocity = {1000, 0};
        bool deleted = false;

        void onCollision(Element *other);

    public:
        Projectile(Vector initialPosition);

        void update();
        void render();
        bool isDeleted();
    };
}