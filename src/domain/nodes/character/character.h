#pragma once
#include <string>
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
        int initialTileColumnLimit = 0;
        int initialTileRowLimit = 0;
        int finalTileColumnLimit = 0;
        int finalTileRowLimit = 0;
        int life = 100;

        VisualElement sprite;
        RendererPort *renderer;

    public:
        Character(
            RendererPort *_renderer,
            TimeManagerPort *_timeManager,
            int width,
            int height,
            std::string_view hexColor);

        void setTilePosition(Vector tilePosition);
        int getWidth();
        int getHeight();
        void render();
        void setTileLimits(int initialTileColumnIndex, int finalTileColumnIndex, int initialTileRowIndex, int finalTileRowIndex);

        virtual ~Character() = default;
    };
}