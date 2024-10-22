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

    std::string name;
    std::string description;
    WeaponFactory *weaponFactory = nullptr;
    Sprite iconSprite;
    Sprite cardSprite;

  public:
    Card(const CardConfig cardConfig);

    std::string getName() const
    {
      return this->name;
    }

    std::string getDescription() const
    {
      return this->description;
    }

    const Sprite &getIconSprite() const
    {
      return this->iconSprite;
    }

    const Sprite &getCardSprite() const
    {
      return this->cardSprite;
    }

    void setSpriteSize(const float width, const float height)
    {
      this->cardSprite.setWidth(width);
      this->cardSprite.setHeight(height);
    }

    void setIconSpriteSize(const float width, const float height)
    {
      this->iconSprite.setWidth(width);
      this->iconSprite.setHeight(height);
    }

    Weapon *createWeapon(const ChildWeaponConfig &weaponConfig) const
    {
      return this->weaponFactory->createWeapon(weaponConfig);
    }
  };
}