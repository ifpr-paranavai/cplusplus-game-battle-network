#pragma once
#include <string>
#include "../../../utils/global/global.h"
#include "../../../utils/math/vector.h"
#include "../visual-element/visual-element.h"
#include "../tile-map/tile-map.h"
#include "../element/element.h"

namespace Game
{
    class Character : public Element
    {
    protected:
        Vector tilePosition;
        Vector tileXLimit;
        Vector tileYLimit;
        int life = 100;

        VisualElement sprite;

    public:
        Character(
            int width,
            int height,
            std::string_view hexColor);

        void setTilePosition(Vector tilePosition);
        int getWidth();
        int getHeight();
        void render();
        void setTileXLimit(Vector tileXLimit);
        void setTileYLimit(Vector tileYLimit);

        virtual ~Character() = default;
    };
}