#pragma once
#include "../tiled-game-object/tiled-game-object.h"

namespace Game
{
  class TileBasedAttack : public TiledGameObject
  {
  protected:
    int damage;
    bool deleted = false;

  public:
    TileBasedAttack() {}

    int getDamage()
    {
      return this->damage;
    }

    bool isDeleted()
    {
      return this->deleted;
    }
  };
}