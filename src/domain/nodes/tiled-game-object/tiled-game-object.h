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
    void setTilePosition(Vector tilePosition)
    {
      this->tilePosition = tilePosition;
      this->position = TileMap::getElementPositionInTile(this->tilePosition, this->width, this->height);
    }

    void setTileXLimit(Vector tileXLimit)
    {
      this->tileXLimit = tileXLimit;
    }

    void setTileYLimit(Vector tileYLimit)
    {
      this->tileYLimit = tileYLimit;
    }
  };
}