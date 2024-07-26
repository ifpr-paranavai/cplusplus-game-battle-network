#pragma once
#include <list>
#include "../../nodes/tile-based-attack/tile-based-attack.h"
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../nodes/visual-element/visual-element.h"

namespace Game
{
    class Flamethrower : public TileBasedAttack
    {
    private:
        float increaseFlameTime = 0.75;
        float increaseFlameTimer = 0;
        std::list<VisualElement> flames;

        void handleFlameIncrease();
        void increaseFlame();

    protected:
        void onCollision(Element *other) override;

    public:
        Flamethrower(Vector initialTilePoition);

        void update() override;
        void render() override;
    };
}