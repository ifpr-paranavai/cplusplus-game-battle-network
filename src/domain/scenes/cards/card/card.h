#pragma once
#include <string_view>
#include "../../../nodes/weapon/weapon.h"
#include "../../../nodes/sprite/sprite.h"

namespace Game
{

  class WeaponFactory
  {
  public:
    virtual Weapon *createWeapon(const ChildWeaponConfig &weaponConfig) = 0;
  };

  class Card
  {
  private:
    struct CardConfig
    {
      std::string_view name;
      std::string_view description;
      WeaponFactory *weaponFactory;
      Sprite iconSprite;
    };

    std::string_view name;
    std::string_view description;
    WeaponFactory *weaponFactory = nullptr;
    Sprite iconSprite;
    Sprite cardSprite;

  public:
    Card(const CardConfig cardConfig);

    std::string_view getName() const
    {
      return this->name;
    }

    std::string_view getDescription() const
    {
      return this->description;
    }

    Sprite &getIconSprite()
    {
      return this->iconSprite;
    }

    Sprite &getCardSprite()
    {
      return this->cardSprite;
    }

    Weapon *createWeapon(const ChildWeaponConfig &weaponConfig) const
    {
      return this->weaponFactory->createWeapon(weaponConfig);
    }
  };
}