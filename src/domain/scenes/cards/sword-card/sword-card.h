#pragma once
#include "../card/card.h"
#include "../../weapons/sword/sword.h"

namespace Game
{

  class SwordWeaponFactory : public WeaponFactory
  {
  public:
    Weapon *createWeapon(const ChildWeaponConfig &weaponConfig) override
    {
      return new Sword(weaponConfig);
    }
  };

  class SwordCard : public Card
  {
  public:
    SwordCard() : Card({"Espada",
                        "Causa 50 de dano ao chão diretamente a frente",
                        new SwordWeaponFactory(),
                        Sprite({27, 10, "assets/sprites/weapons/sword/icon/0.png", false, Vector{0, 0}})}) {}
  };
}