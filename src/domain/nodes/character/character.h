#pragma once
#include <string>
#include "../../../utils/global/global.h"
#include "../../../utils/math/vector.h"
#include "../visual-element/visual-element.h"
#include "../tile-based-body/tile-based-body.h"

namespace Game
{
    class Character : public TileBasedBody
    {
    protected:
        int life = 100;

        VisualElement sprite;

    public:
        Character(
            int width,
            int height,
            std::string_view hexColor);

        int getWidth();
        int getHeight();
        void render();

        virtual ~Character() = default;
    };
}