#pragma once
#include "../element/element.h"
#include "../../dto/vector/vector.h"
#include "../../../utils/global-adapters/global-adapters.h"

namespace Game
{
    class DynamicBody : public Element
    {

    protected:
        float downForce = 0;
        float movementTime = 0;
        float movementTimer = 0;
        bool movementFinished = false;
        Vector velocity = {0, 0};

    public:
        DynamicBody(int width, int height);

        void move();
    };
}