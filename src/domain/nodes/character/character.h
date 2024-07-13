#pragma once
#include <string>
#include "../visual-element/visual-element.h"
#include "../tile-map/tile-map.h"
#include "../element/element.h"

namespace Game
{
    class Character : public Element
    {
    protected:
        int tileColumnIndex = 0;
        int tileRowIndex = 0;
        int initialTileColumnLimit = 0;
        int initialTileRowLimit = 0;
        int finalTileColumnLimit = 0;
        int finalTileRowLimit = 0;
        int life = 100;

        VisualElement *sprite;
        RendererPort *renderer;

    public:
        Character(
            RendererPort *_renderer,
            TimeManagerPort *_timeManager,
            int width,
            int height,
            std::string_view hexColor);

        void setTileCoords(int tileColumnIndex, int tileRowIndex);
        void setTileColumnIndex(int tileColumnIndex);
        void setTileRowIndex(int tileRowInde);
        int getWidth();
        int getHeight();
        void render();
        void setTileLimits(int initialTileColumnIndex, int finalTileColumnIndex, int initialTileRowIndex, int finalTileRowIndex);

        virtual ~Character() = default;
    };
}