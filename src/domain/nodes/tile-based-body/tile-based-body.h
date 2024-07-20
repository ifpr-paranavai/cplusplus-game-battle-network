#pragma once
#include "../element/element.h"
#include "../tile-map/tile-map.h"

namespace Game
{
    class TileBasedBody : public Element
    {
    protected:
        Vector tilePosition;
        Vector tileXLimit;
        Vector tileYLimit;

        bool tryMoveUp();
        bool tryMoveDown();
        bool tryMoveLeft();
        bool tryMoveRight();

    public:
        TileBasedBody(int width, int height);

        void setTilePosition(Vector tilePosition);
        void setTileXLimit(Vector tileXLimit);
        void setTileYLimit(Vector tileYLimit);
    };
}