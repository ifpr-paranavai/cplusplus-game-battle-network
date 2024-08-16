#pragma once
#include <string>
#include <list>
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../global/global-services/global-services.h"
#include "../../dto/vector/vector.h"
#include "../tile-based-body/tile-based-body.h"
#include "../animated-sprited/animated-sprited.h"

namespace Game
{
    class Character : public TileBasedBody
    {
    private:
        AnimatedSprite *currentAnimatedSprite = nullptr;

    protected:
        int life = 100;

        void updateCurrentAnimatedSprite(AnimatedSprite *newAnimatedSprite);

    public:
        Character(
            int width,
            int height);

        virtual void render()
        {
            this->currentAnimatedSprite->renderSprite(this->position);
            for (const CollisionBox &collisionBox : this->collisionBoxes)
            {
                collisionBox.renderCollisionBox();
            }
        }

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