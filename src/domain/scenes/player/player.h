#pragma once
#include <iostream>
#include <ctime>
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../../ports/keyboard-manager/keyboard-manager.h"
#include "../attacks/projectile/projectile.h"
#include "../../../utils/log-manager/log-manager.h"
#include "../../global/global-services/global-services.h"
#include "../../nodes/tile-based-attack/tile-based-attack.h"
#include "../weapons/pistol/pistol.h"
#include "../weapons/sniper/sniper.h"
#include "../weapons/sword/sword.h"
#include "../../../utils/timer-subject/timer-subject.h"
#include "../cards/card/card.h"
#include "../../nodes/actor/actor.h"

namespace Game
{
  class Player : public Actor
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

    class BlockWeaponAttackHandler : public Observer<int>
    {
    private:
      Player &player;

    public:
      BlockWeaponAttackHandler(Player &_player) : player(_player) {}

      void next(const int &value) override
      {
        this->player.canAttack = false;
      }
    };

    class UnblockWeaponAttackHandler : public Observer<int>
    {
    private:
      Player &player;

    public:
      UnblockWeaponAttackHandler(Player &_player) : player(_player) {}

      void next(const int &value) override
      {
        this->player.canAttack = true;
      }
    };

    class ResetWeaponToPistolHandler : public Observer<int>
    {
    private:
      Player &player;

    public:
      ResetWeaponToPistolHandler(Player &_player) : player(_player) {}

      void next(const int &value) override
      {
        this->player.canAttack = true;
        this->player.currentWeapon = &this->player.pistol;
      }
    };

    class SetSelectedCardHandler : public Observer<Card>
    {
    private:
      Player &player;

    public:
      SetSelectedCardHandler(Player &_player) : player(_player) {}

      void next(const Card &value) override
      {
        const Game::Card *cardPtr = &value;
        player.selectedCard = const_cast<Game::Card *>(cardPtr);
      }
    };

    AnimatedSprite idleSprite = AnimatedSprite({0.1f,
                                                "assets/sprites/player/idle",
                                                8,
                                                120,
                                                120,
                                                false,
                                                Vector(-((120 - 96) / 2), -((120 - 96) / 2))});
    ResetWeaponToPistolHandler *resetWeaponToPistolHandler = new ResetWeaponToPistolHandler(*this);
    BlockWeaponAttackHandler *blockWeaponAttackHandler = new BlockWeaponAttackHandler(*this);
    UnblockWeaponAttackHandler *unblockWeaponAttackHandler = new UnblockWeaponAttackHandler(*this);
    SetSelectedCardHandler *setSelectedCardHandler = new SetSelectedCardHandler(*this);
    InvencibilityHandler invencibilityHandler = InvencibilityHandler(*this);
    Pistol pistol = Pistol({{39, 28}, this->blockWeaponAttackHandler, this->unblockWeaponAttackHandler});
    Weapon *currentWeapon = &this->pistol;
    Card *selectedCard = nullptr;
    TimerSubject invencibleTimer;
    bool invencible = false;
    bool canAttack = true;

    void handleMovement();
    void handleAttack();
    void handleAttackWithCard();

  public:
    Player();
    ~Player();
    void update() override;
    void onCollision(GameObject *other) override;
    void render(const Vector &basePosition = {0, 0}) const override;

    SetSelectedCardHandler *getSetSelectedCardHandler()
    {
      return this->setSelectedCardHandler;
    }
  };
}