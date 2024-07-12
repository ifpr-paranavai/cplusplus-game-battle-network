#pragma once
#include "../../nodes/visual-element/visual-element.h"
#include "../../nodes/element/element.h"

namespace Game
{
    class Projectile : public Element
    {
    private:
        VisualElement *sprite;
        int speedVel = 10;
        bool deleted = false;

        void onCollision(Element *other);

    public:
        Projectile(RendererPort *_renderer, int initialX, int initialY);

        void update();
        void render();
        bool isDeleted();
    };
}