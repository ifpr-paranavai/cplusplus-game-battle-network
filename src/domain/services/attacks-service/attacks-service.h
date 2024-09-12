#pragma once
#include <list>
#include <memory>
#include "../../nodes/dynamic-attack/dynamic-attack.h"
#include "../../nodes/tile-based-attack/tile-based-attack.h"

namespace Game
{
  class AttacksService
  {
    std::list<std::unique_ptr<DynamicAttack>> dynamicAttacks;
    std::list<std::unique_ptr<TileBasedAttack>> tileBasedAttacks;

  public:
    ~AttacksService() = default;
    void removeExpiredAttacks();

    auto addDynamicAttack(std::unique_ptr<DynamicAttack> projectile)
    {
      dynamicAttacks.push_back(std::move(projectile));
      return std::prev(dynamicAttacks.end());
    }

    auto addTileBasedAttack(std::unique_ptr<TileBasedAttack> tileBasedAttack)
    {
      tileBasedAttacks.push_back(std::move(tileBasedAttack));
      return std::prev(tileBasedAttacks.end());
    }

    void removeDynamicAttack(std::list<std::unique_ptr<DynamicAttack>>::iterator attackIt)
    {
      if (attackIt != dynamicAttacks.end())
      {
        dynamicAttacks.erase(attackIt);
      }
    }

    void removeTileBasedAttack(std::list<std::unique_ptr<TileBasedAttack>>::iterator attackIt)
    {
      if (attackIt != tileBasedAttacks.end())
      {
        tileBasedAttacks.erase(attackIt);
      }
    }

    const auto &getDynamicAttacks() const
    {
      return dynamicAttacks;
    }

    const auto &getTileBasedAttacks() const
    {
      return tileBasedAttacks;
    }
  };
}
