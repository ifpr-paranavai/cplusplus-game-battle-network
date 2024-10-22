#include "pistol.h"

namespace Game
{

  Pistol::Pistol(const ChildWeaponConfig pistolConfig) : Weapon({pistolConfig.relativePosition,
                                                                 5,
                                                                 new AnimatedSprite({0,
                                                                                 "assets/sprites/weapons/pistol/idle",
                                                                                 1,
                                                                                 100,
                                                                                 60,
                                                                                 false,
                                                                                 Vector(0, 0)}),
                                                                 pistolConfig.attackInitObserver,
                                                                 pistolConfig.attackEndObserver})
  {
    this->shootAnimation.subscribeToAnimationEnd(&this->idleModeHandler);
    this->shootAnimation.subscribeToAnimationEnd(pistolConfig.attackEndObserver);
  }

  Pistol::~Pistol()
  {
    Global::adaptersInstance.audioManager->freeSoundEffect(this->projectileSFX);
  }

  void Pistol::attack(const Vector elementPosition, const Vector elementTilePosition)
  {
    if (!this->canAttack)
    {
      return;
    }
    this->canAttack = false;
    const Vector absolutePosition = elementPosition + this->relativePosition;
    const Vector projectilePosition(absolutePosition.x + this->spriteWidth, absolutePosition.y);
    std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(projectilePosition, this->damage);
    Global::attacksService->addDynamicAttack(std::move(projectile));
    this->queueAnimationChange(&this->shootAnimation);
    Global::adaptersInstance.audioManager->playWavSoundEffect(this->projectileSFX);
  }

}