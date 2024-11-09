#include "tile.h"

namespace Game
{
  Tile::Tile(int width, int height, Vector position, bool _isPlayerTile) : isPlayerTile(_isPlayerTile)
  {
    this->width = width;
    this->height = height;
    this->position = position;
    this->configureSprites();
  }

  void Tile::configureSprites()
  {
    const int spriteWidth = std::round(this->width / 4);
    const int spriteHeight = std::round(this->height / 3);
    const std::string initialSpritePath = "assets/sprites/tilemap/";
    const std::vector spritePaths = {
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
    const std::vector spritePositions = {
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

  void Tile::createSprite(std::string_view path, const Vector &position, int width, int height)
  {
    const Sprite sprite = Sprite({width,
                                  height,
                                  path,
                                  false,
                                  position,
                                  this->isPlayerTile ? this->playerTileColor : this->enemyTileColor});
    this->sprites.emplace_back(std::move(sprite));
  }

  void Tile::render(const Vector &basePosition) const
  {
    for (const Sprite &sprite : this->sprites)
    {
      sprite.render(this->position);
    }
  }
}
