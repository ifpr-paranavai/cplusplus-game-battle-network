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
        int tileColumnIndexLimit = 0;
        int tileRowLimit = 0;
        int life = 100;

        VisualElement *sprite;
        RendererPort *renderer;

    public:
        Character(RendererPort *_renderer, int width, int height, std::string_view hexColor);

        void setTileCoords(int tileColumnIndex, int tileRowIndex);
        void setTileColumnIndex(int tileColumnIndex);
        void setTileRowIndex(int tileRowInde);
        int getWidth();
        int getHeight();
        void render();
        void setTileLimits(int tileColumnIndex, int tileRowIndex);

        virtual ~Character() = default;
    };
}