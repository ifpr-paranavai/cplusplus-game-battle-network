#include "fireman.h"

namespace Game
{
  FiremanEnemy::FiremanEnemy()
  {
    this->width = 96;
    this->height = 96;
    this->attackTime = 3;
    this->life = 300;
    this->queueAnimationChange(&this->idleSprite);

    this->fireAttackAnimation.subscribeToAnimationEnd(this->idleAnimationHandler.get());
    this->throwingAttackAnimation.subscribeToAnimationEnd(this->idleAnimationHandler.get());
    this->attackDelaySubject.subscribe(this->unlockMovementHandler.get());
  }

  void FiremanEnemy::attack()
  {
    const int randomAttackIndex = std::rand() % 2;
    const Attacks choicedAttack = static_cast<Attacks>(randomAttackIndex);
    switch (choicedAttack)
    {
    case Attacks::FLAMETHROWER:
      this->flamethrowerAttack();
      break;
    case Attacks::BOMB:
      this->bombAttack();
      break;
    default:
      throw std::runtime_error("Invalid attack");
    }
  }

  void FiremanEnemy::flamethrowerAttack()
  {
    this->lockMovement();
    this->attackDelaySubject.init(3);
    this->queueAnimationChange(&this->fireAttackAnimation);
    const float yTileDecision = std::rand() % 3;
    this->setTilePosition({this->tileXLimit[0], yTileDecision});
    Global::attacksService->addTileBasedAttack(std::make_unique<FlamethrowerAttack>(this->tilePosition));
  }

  void FiremanEnemy::bombAttack()
  {
    this->queueAnimationChange(&this->throwingAttackAnimation);
    this->lockMovement();
    Global::attacksService->addDynamicAttack(std::make_unique<BombAttack>(this->tilePosition));
    this->attackDelaySubject.init(1.5f);
  }

  void FiremanEnemy::update()
  {
    this->attackDelaySubject.update();
    Enemy::update();
  }

  void FiremanEnemy::onCollision(GameObject *other)
  {
    if (dynamic_cast<BombAttack *>(other))
    {
      return;
    }

    Enemy::onCollision(other);
  }

  void FiremanEnemy::unlockMovement()
  {
    this->canMove = true;
    this->canAttack = true;
  }

  void FiremanEnemy::lockMovement()
  {
    this->canAttack = false;
    this->canMove = false;
  }

}