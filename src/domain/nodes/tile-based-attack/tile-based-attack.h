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

    inline int getDamage() { return this->damage; }
    inline bool isDeleted() { return this->deleted; }
  };
}