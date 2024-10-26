#pragma once
#include <list>
#include <vector>
#include "../../nodes/visual-entity/visual-entity.h"
#include "../../nodes/sprite/sprite.h"

namespace Game
{
    class Tile : public VisualEntity
    {
    private:
        const Color playerTileColor = Color{255, 69, 0, 255};
        const Color enemyTileColor = Color{65, 105, 225, 255};
        const bool isPlayerTile = false;
        std::list<Sprite> sprites;

        void configureSprites();
        void createSprite(std::string_view path, const Vector &position, float width, float height);

    public:
        Tile(int width, int height, Vector position, bool isPlayerTile = true);

        void update() override {}
        void render() const override;
    };
}