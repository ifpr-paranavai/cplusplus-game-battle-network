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
        AnimatedSprite *currentAnimation = nullptr;
        AnimatedSprite *pendingAnimation = nullptr;

        void applyPendingAnimation();

    protected:
        int life = 100;

        void queueAnimationChange(AnimatedSprite *newAnimation)
        {
            this->pendingAnimation = newAnimation;
        }

    public:
        Character(
            int width,
            int height);

        void update() override
        {
            this->applyPendingAnimation();
        }

        virtual void render()
        {
            this->currentAnimation->renderSprite(this->position);
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