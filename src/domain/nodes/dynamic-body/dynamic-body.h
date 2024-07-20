#pragma once
#include "../element/element.h"
#include "../../../utils/math/vector.h"
#include "../../../utils/global-adapters/global-adapters.h"

namespace Game
{
    class DynamicBody : public Element
    {

    protected:
        Vector velocity = {0, 0};
        void move();

    public:
        DynamicBody(int width, int height);
    };
}