#pragma once
#include "../../../global/global-services/global-services.h"
#include "../../../nodes/dynamic-attack/dynamic-attack.h"
#include "../../../nodes/tile-map/tile-map.h"

namespace Game
{
    class BombAttack : public DynamicAttack
    {
    private:
        const float maxHeight = 100;
        float inTileTimer = 1;
        bool inTile = false;
        float xDistance;
        Vector initialPosition;
        Vector targetPosition;

        void calculatePositions(Vector elementTilePosition);
        void defineVelocity();
        void handleTargetReached();
        void checkInTileTimer();

    protected:
        void onCollision(Element *other) override;

    public:
        BombAttack(Vector elementPosition);

        void update() override;
    };
}