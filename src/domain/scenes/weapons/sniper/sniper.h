#pragma once
#include "../../../nodes/weapon/weapon.h"
#include "../../attacks/projectile/projectile.h"

namespace Game
{
  class Sniper : public Weapon
  {
  private:
    const float spriteWidth = 160;
    const float spriteHeight = 40;
    const SoundEffect projectileSFX = Global::adaptersInstance.audioManager->initSoundEffect("assets/sounds/projectile.wav");

    AnimatedSprite shootAnimation = AnimatedSprite({0.01f,
                                                    "assets/sprites/weapons/sniper/shooting",
                                                    28,
                                                    200,
                                                    this->spriteHeight,
                                                    false,
                                                    Vector(0, 0)});

  public:
    Sniper(const ChildWeaponConfig sniperConfig);

    void attack(const Vector initialPosition, const Vector elementTilePosition) override;

    void render(const Vector position) override
    {
      Weapon::render(position);
      if (this->currentAnimation != this->idleAnimation)
      {
        this->idleAnimation->renderSprite(position + this->relativePosition);
      }
    }
  };
}