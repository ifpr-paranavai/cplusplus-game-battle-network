#pragma once
#include <list>
#include <string>
#include <array>
#include "../../../utils/math/vector.h"
#include "../visual-element/visual-element.h"
#include "../element/element.h"

namespace Game
{
    class Tile : public Element
    {
    protected:
        virtual void onCollision(Element *other) {}

    private:
        std::list<VisualElement> sprites;
        bool isPlayerTile = false;

        void configureSprites();
        void createSprite(std::string_view path, const Vector &position, float width, float height);

    public:
        Tile(int width, int height, Vector position, bool isPlayerTile = true);

        void renderSprites() const;
    };
}