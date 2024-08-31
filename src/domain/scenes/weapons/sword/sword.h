#pragma once
#include <iostream>
#include "../../../nodes/weapon/weapon.h"
#include "../../../nodes/collision-box/collision-box.h"
#include "../../attacks/stab/stab.h"
#include "../../../../utils/subject/subject.h"

namespace Game
{
  class Sword : public Weapon
  {
  private:
    class SwordIdleModeHandler : public WeaponIdleModeHandler
    {
    private:
      Sword &sword;

    public:
      SwordIdleModeHandler(Sword &_sword) : WeaponIdleModeHandler(_sword), sword(_sword) {}

      void next(const int &value) override
      {
        WeaponIdleModeHandler::next(value);
        Global::attacksService->removeTileBasedAttack(this->sword.stabAttackIt);
      }
    };

    AnimatedSprite stabAnimation = AnimatedSprite({
        0.1f,
        "assets/sprites/weapons/sword/stab",
        8,
        102,
        20,
        false,
        Vector(0, 0),
    });
    std::list<std::unique_ptr<TileBasedAttack>>::iterator stabAttackIt;

  public:
    Sword(const ChildWeaponConfig swordConfig);

    void attack(const Vector initialPosition, const Vector elementTilePosition) override;
  };
}
