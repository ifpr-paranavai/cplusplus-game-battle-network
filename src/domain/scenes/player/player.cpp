#include "player.h"

namespace Game
{
  Player::Player()
  {
    this->width = 96;
    this->height = 96;
    this->life = 100;
    this->queueAnimationChange(&this->idleSprite);
    this->collisionBoxes.emplace_back(this->position, this->width, 30);
    this->invencibleTimer.subscribe(&this->invencibilityHandler);
  }

  Player::~Player()
  {
    delete resetWeaponToPistolHandler;
    delete blockWeaponAttackHandler;
    delete unblockWeaponAttackHandler;
    delete setSelectedCardHandler;
  }

  void Player::handleMovement()
  {
    const auto &keyboardManager = Global::adaptersInstance.keyboardManager;
    if (keyboardManager->isKeyPressed(KeyCode::ARROW_UP))
    {
      this->tryMoveUp();
    }
    else if (keyboardManager->isKeyPressed(KeyCode::ARROW_DOWN))
    {
      this->tryMoveDown();
    }
    else if (keyboardManager->isKeyPressed(KeyCode::ARROW_LEFT))
    {
      this->tryMoveLeft();
    }
    else if (keyboardManager->isKeyPressed(KeyCode::ARROW_RIGHT))
    {
      this->tryMoveRight();
    }
  }

  void Player::handleAttack()
  {
    if (this->canAttack && Global::adaptersInstance.keyboardManager->isKeyPressed(KeyCode::X))
    {
      this->currentWeapon->attack(this->position, this->tilePosition);
    }
  }

  void Player::handleAttackWithCard()
  {
    if (this->selectedCard == nullptr)
    {
      return;
    }

    if (Global::adaptersInstance.keyboardManager->isKeyPressed(KeyCode::C))
    {
      this->currentWeapon = this->selectedCard->createWeapon({{59, 38}, this->blockWeaponAttackHandler, this->resetWeaponToPistolHandler});
      this->currentWeapon->attack(this->position, this->tilePosition);
      this->selectedCard = nullptr;
    }
  }

  void Player::update()
  {
    this->handleMovement();
    this->handleAttack();
    this->handleAttackWithCard();
    for (CollisionBox &collisionBox : this->collisionBoxes)
    {
      collisionBox.setPosition(this->position + Vector{0, 40});
    }
    this->currentWeapon->update();
    this->invencibleTimer.update();
    Actor::update();
  }

  void Player::onCollision(GameObject *other)
  {
    if (dynamic_cast<Projectile *>(other) || this->invencible || this->life <= 0)
    {
      return;
    }

    if (auto attack = dynamic_cast<DynamicAttack *>(other))
    {
      this->life -= attack->getDamage();
      this->invencible = true;
    }
    else if (auto tileBasedAttack = dynamic_cast<TileBasedAttack *>(other))
    {
      this->life -= tileBasedAttack->getDamage();
      this->invencible = true;
    }

    if (this->invencible)
    {
      this->invencibleTimer.init(1);
    }

    if (this->life <= 0)
    {
      this->life = 0;
      this->onDeath.next(0);
    }
  }

  void Player::render(const Vector &basePosition) const
  {
    Actor::render();
    this->currentWeapon->render(this->position);
    if (this->selectedCard != nullptr)
    {
      this->selectedCard->getIconSprite().render(this->position);
    }
  }
}
