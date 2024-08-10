#pragma once
#include <list>
#include <string>
#include <array>
#include "../../dto/vector/vector.h"
#include "../element/element.h"
#include "../sprite/sprite.h"
#include "../../dto/color/color.h"

namespace Game
{
    class Tile : public Element
    {
    protected:
        virtual void onCollision(Element *other) {}

    private:
        const Color playerTileColor = Color{255, 69, 0, 255};
        const Color enemyTileColor = Color{65, 105, 225, 255};
        const bool isPlayerTile = false;
        std::list<Sprite> sprites;

        void configureSprites();
        void createSprite(std::string_view path, const Vector &position, float width, float height);

    public:
        Tile(int width, int height, Vector position, bool isPlayerTile = true);

        void renderSprites() const;
    };
}