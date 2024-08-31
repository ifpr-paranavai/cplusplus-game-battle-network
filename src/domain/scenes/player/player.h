#pragma once
#include <iostream>
#include <ctime>
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../nodes/character/character.h"
#include "../../../ports/keyboard-manager/keyboard-manager.h"
#include "../attacks/projectile/projectile.h"
#include "../../../utils/log-manager/log-manager.h"
#include "../../global/global-services/global-services.h"
#include "../../nodes/tile-based-attack/tile-based-attack.h"
#include "../weapons/pistol/pistol.h"
#include "../weapons/sniper/sniper.h"
#include "../weapons/sword/sword.h"
#include "../../../utils/timer-subject/timer-subject.h"

namespace Game
{
  class Player : public Character
  {
  private:
    class InvencibilityHandler : public Observer<int>
    {
    private:
      Player &player;

    public:
      InvencibilityHandler(Player &_player) : player(_player) {}

      void next(const int &value) override
      {
        player.invencible = false;
      }
    };

    class BlockWeaponChangeHandler : public Observer<int>
    {
    private:
      Player &player;

    public:
      BlockWeaponChangeHandler(Player &_player) : player(_player) {}

      void next(const int &value) override
      {
        this->player.canChangeWeapon = false;
      }
    };

    class UnblockWeaponChangeHandler : public Observer<int>
    {
    private:
      Player &player;

    public:
      UnblockWeaponChangeHandler(Player &_player) : player(_player) {}

      void next(const int &value) override
      {
        this->player.canChangeWeapon = true;
      }
    };

    AnimatedSprite idleSprite = AnimatedSprite({0.1f,
                                                "assets/sprites/player/idle",
                                                8,
                                                120,
                                                120,
                                                false,
                                                Vector(-((120 - this->width) / 2), -((120 - this->height) / 2))});
    UnblockWeaponChangeHandler *unblockWeaponChangeHandler = new UnblockWeaponChangeHandler(*this);
    BlockWeaponChangeHandler *blockWeaponChangeHandler = new BlockWeaponChangeHandler(*this);
    Pistol pistol = Pistol({{39, 28}, this->blockWeaponChangeHandler, this->unblockWeaponChangeHandler});
    Sniper sniper = Sniper({{39, 28}, this->blockWeaponChangeHandler, this->unblockWeaponChangeHandler});
    Sword sword = Sword({{59, 38}, this->blockWeaponChangeHandler, this->unblockWeaponChangeHandler});
    Weapon *currentWeapon = &this->pistol;
    TimerSubject invencibleTimer;
    bool invencible = false;
    bool canChangeWeapon = true;

    void handleMovement();
    void handleAttack();
    void handleChangeWeapon();

  public:
    Player();
    void update() override;
    void onCollision(Element *other) override;
    void render() override;
  };
}