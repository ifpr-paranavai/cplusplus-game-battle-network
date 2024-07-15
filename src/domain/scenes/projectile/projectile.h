#pragma once
#include "../../nodes/visual-element/visual-element.h"
#include "../../nodes/element/element.h"
#include "../../../config/config.h"

namespace Game
{
    class Projectile : public Element
    {
    private:
        VisualElement *sprite;
        int speedVel = 1000;
        bool deleted = false;

        void onCollision(Element *other);

    public:
        Projectile(RendererPort *_renderer, TimeManagerPort *_timeManager, int initialX, int initialY);

        void update();
        void render();
        bool isDeleted();
    };
}