#pragma once
#include "../../dto/vector/vector.h"
#include "../../../config/config.h"
#include "../../../utils/global-adapters/global-adapters.h"

namespace Game
{
    class CollisionBox
    {
    private:
        int width;
        int height;
        Vector position;

    public:
        CollisionBox(Vector position, int with, int height);
        void setPosition(Vector position);
        bool collidesWith(CollisionBox &other);
        Vector getPosition();
        int getWidth();
        int getHeight();

        void renderCollisionBox() const
        {
            if (Game::Config::SHOW_HITBOXES)
            {
                Global::adaptersInstance.renderer->renderElement({
                    {this->position.x, this->position.y},
                    this->width + 0.0f,
                    this->height + 0.0f,
                    "#000000",
                });
            }
        }
    };
}
