#pragma once
#include "../game-object/game-object.h"
#include "../../scenes/tile-map/tile-map.h"

namespace Game
{
  class TiledGameObject : public GameObject
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
    inline void setTileXLimit(const Vector tileXLimit) { this->tileXLimit = tileXLimit; }
    inline void setTileYLimit(const Vector tileYLimit) { this->tileYLimit = tileYLimit; }

    void setTilePosition(const Vector tilePosition)
    {
      this->tilePosition = tilePosition;
      this->position = TileMap::getElementPositionInTile(this->tilePosition, this->width, this->height);
    }
  };
}