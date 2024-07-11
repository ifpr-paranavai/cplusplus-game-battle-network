#pragma once
#include "../visual-element/visual-element.h"
#include "../tile-map/tile-map.h"

namespace Game
{
    class Character
    {
    protected:
        int width = 0;
        int height = 0;
        int tileColumnIndex = 0;
        int tileRowIndex = 0;
        int tileColumnIndexLimit = 0;
        int tileRowLimit = 0;
        VisualElement *sprite;

    public:
        Character(RendererPort *_renderer, int width, int height, std::string_view hexColor);

        void setTilePosition(int tileColumnIndex, int tileRowIndex);
        int getWidth();
        int getHeight();
        void render();
        void setTileLimits(int tileColumnIndex, int tileRowIndex);

        virtual void update() = 0;
        virtual ~Character() = default;
    };
}