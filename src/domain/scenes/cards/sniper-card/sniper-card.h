#pragma once
#include "../card/card.h"
#include "../../weapons/sniper/sniper.h"

namespace Game
{
  class SniperWeaponFactory : public WeaponFactory
  {
    Weapon *createWeapon(const ChildWeaponConfig &weaponConfig) override
    {
      return new Sniper(weaponConfig);
    }
  };

  class SniperCard : public Card
  {
  public:
    SniperCard() : Card({"Sniper",
                         "Causa 25 de dano ao inimigo disparando um projetíl em linha reta",
                         new SniperWeaponFactory(),
                         Sprite({16, 4, "assets/sprites/weapons/sniper/idle/0.png", false, Vector{0, 0}})}) {}
  };
}
