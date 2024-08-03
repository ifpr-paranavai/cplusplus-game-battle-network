#include "tile.h"

namespace Game
{
    Tile::Tile(int width, int height, Vector position, bool isPlayerTile) : Element(width, height)
    {
        this->isPlayerTile = isPlayerTile;
        this->position = position;
        this->configureSprites();
    }

    void Tile::configureSprites()
    {
        const float spriteWidth = this->width / 4;
        const float spriteHeight = this->height / 3;
        const std::string initialSpritePath = "assets/sprites/tilemap/";
        const std::array<std::string, 12> spritePaths = {
            initialSpritePath + "left-top.png",
            initialSpritePath + "middle-top.png",
            initialSpritePath + "middle-top.png",
            initialSpritePath + "right-top.png",
            initialSpritePath + "left-middle.png",
            initialSpritePath + "middle-middle.png",
            initialSpritePath + "middle-middle.png",
            initialSpritePath + "right-middle.png",
            initialSpritePath + "left-bottom.png",
            initialSpritePath + "middle-bottom.png",
            initialSpritePath + "middle-bottom.png",
            initialSpritePath + "right-bottom.png"};
        const std::array<Vector, 12> spritePositions = {
            Vector(0, 0),
            Vector(spriteWidth, 0),
            Vector(spriteWidth * 2, 0),
            Vector(spriteWidth * 3, 0),
            Vector(0, spriteHeight),
            Vector(spriteWidth, spriteHeight),
            Vector(spriteWidth * 2, spriteHeight),
            Vector(spriteWidth * 3, spriteHeight),
            Vector(0, spriteHeight * 2),
            Vector(spriteWidth, spriteHeight * 2),
            Vector(spriteWidth * 2, spriteHeight * 2),
            Vector(spriteWidth * 3, spriteHeight * 2)};

        for (size_t i = 0; i < spritePaths.size(); ++i)
        {
            this->createSprite(spritePaths[i], spritePositions[i], spriteWidth, spriteHeight);
        }
    }

    void Tile::createSprite(std::string_view path, const Vector &position, float width, float height)
    {
        const Vector absolutePosition = this->position + position;
        VisualElement sprite;
        sprite.setSpritePath(path);
        sprite.setSpriteColorFilter(this->isPlayerTile ? Color{255, 69, 0, 255} : Color{65, 105, 225, 255});
        sprite.setConfig("#FFFFFF", absolutePosition, width, height);
        this->sprites.emplace_back(std::move(sprite));
    }

    void Tile::renderSprites() const
    {
        for (const VisualElement &sprite : this->sprites)
        {
            sprite.renderSprite();
        }
    }
}
