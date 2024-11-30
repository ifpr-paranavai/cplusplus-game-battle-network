#include "tiled-game-object.h"

namespace Game
{
  bool TiledGameObject::tryMoveUp()
  {
    if (this->tilePosition.y - 1 < this->tileYLimit[0])
    {
      return false;
    }
    this->setTilePosition({this->tilePosition.x, this->tilePosition.y - 1});
    return true;
  }

  bool TiledGameObject::tryMoveDown()
  {

    if (this->tilePosition.y + 1 > this->tileYLimit[1])
    {
      return false;
    }
    this->setTilePosition({this->tilePosition.x, this->tilePosition.y + 1});
    return true;
  }

  bool TiledGameObject::tryMoveLeft()
  {
    if (this->tilePosition.x - 1 < this->tileXLimit[0])
    {
      return false;
    }
    this->setTilePosition({this->tilePosition.x - 1, this->tilePosition.y});
    return true;
  }

  bool TiledGameObject::tryMoveRight()
  {
    if (this->tilePosition.x + 1 > this->tileXLimit[1])
    {
      return false;
    }
    this->setTilePosition({this->tilePosition.x + 1, this->tilePosition.y});
    return true;
  }
}