#pragma once
#include <list>
#include <vector>
#include "../../nodes/sprite/sprite.h"
#include "../../nodes/game-object/game-object.h"

namespace Game
{
    class Tile : public GameObject
    {
    private:
        const Color playerTileColor = Color{255, 69, 0, 255};
        const Color enemyTileColor = Color{65, 105, 225, 255};
        const bool isPlayerTile = false;
        std::list<Sprite> sprites;

        void configureSprites();
        void createSprite(std::string_view path, const Vector &position, int width, int height);

    public:
        Tile(int width, int height, Vector position, bool isPlayerTile = true);

        void render(const Vector &basePosition = {0, 0}) const override;
        void update() override {}
        void onCollision(GameObject *other) override {}
    };
}