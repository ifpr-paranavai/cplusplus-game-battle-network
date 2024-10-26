#include "bomb-attack.h"

namespace Game
{
  BombAttack::BombAttack(Vector elementTilePosition) : DynamicAttack(elementTilePosition)
  {
    this->width = 32;
    this->height = 32;
    this->movementTime = 1.0f;
    this->damage = 15;
    this->calculatePositions(elementTilePosition);
    this->defineVelocity();
    Global::adaptersInstance.audioManager->playWavSoundEffect(this->grenadeThrowingSFX);
  }

  BombAttack::~BombAttack()
  {
    Global::adaptersInstance.audioManager->freeSoundEffect(this->grenadeThrowingSFX);
    Global::adaptersInstance.audioManager->freeSoundEffect(this->bombExplosionSFX);
    this->currentSprite = nullptr;
  }

  void BombAttack::calculatePositions(Vector elementTilePosition)
  {
    const Vector tileTargetPosition = {elementTilePosition.x - 3, elementTilePosition.y};
    this->targetPosition = TileMap::getElementPositionInTile(tileTargetPosition, this->width, this->height);
    this->initialPosition = TileMap::getElementPositionInTile(elementTilePosition, this->width, this->height);
    this->targetPosition.y += this->height;
    this->initialPosition.y += this->height;
    this->position = this->initialPosition;
    Vector deltaPosition = this->initialPosition - this->targetPosition;
    this->xDistance = deltaPosition.x;
  }

  void BombAttack::defineVelocity()
  {
    this->velocity.x = -this->xDistance / this->movementTime;
    this->downForce = 8 * this->verticalDistance / (this->movementTime * this->movementTime / 4);
    this->velocity.y = -this->downForce * this->movementTime / 2;
  }

  void BombAttack::handleTargetReached()
  {
    if (this->movementFinished)
    {
      this->velocity = {0, 0};
      this->inTile = true;
    }
  }

  void BombAttack::checkExplosionTimer()
  {
    if (!this->inTile || this->alreadyExploded)
    {
      return;
    }

    this->timeToExplosion -= Global::adaptersInstance.timeManager->getDeltaTime();
    if (this->timeToExplosion <= 0)
    {
      this->alreadyExploded = true;
      this->sprites.clear();
      Global::adaptersInstance.audioManager->playWavSoundEffect(this->bombExplosionSFX);
      this->currentSprite = &this->explosionAnimation;
      Global::animationService->addAnimatedSprite(&this->explosionAnimation);
    }
  }

  void BombAttack::checkDeleteTimer()
  {
    if (!this->alreadyExploded)
    {
      return;
    }

    this->timeToDelete -= Global::adaptersInstance.timeManager->getDeltaTime();
    if (this->timeToDelete <= 0)
    {
      this->deleted = true;
      Global::animationService->removeAnimatedSprite(&this->explosionAnimation);
    }
  }

  void BombAttack::update()
  {
    DynamicAttack::update();
    this->handleTargetReached();
    this->checkExplosionTimer();
    this->checkDeleteTimer();
  }

  void BombAttack::render() const
  {
    if (this->currentSprite != nullptr)
    {
      this->currentSprite->renderSprite(this->position);
    }
  }

}
