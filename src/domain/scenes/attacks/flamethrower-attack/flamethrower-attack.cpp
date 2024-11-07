#include "flamethrower-attack.h"

namespace Game
{

  FlamethrowerAttack::FlamethrowerAttack(Vector elementPosition)
  {
    this->width = 60;
    this->height = 80;
    this->damage = 10;
    this->tilePosition = elementPosition;
  }

  void FlamethrowerAttack::handleFlameIncrease()
  {
    this->increaseFlameTimer += Global::adaptersInstance.timeManager->getDeltaTime();
    if (this->increaseFlameTimer < this->increaseFlameTime)
    {
      return;
    }
    this->increaseFlameTimer = 0;
    this->increaseFlame();
  }

  void FlamethrowerAttack::increaseFlame()
  {
    if (this->tilePosition.x - 1 < 0)
    {
      this->deleted = true;
      return;
    }

    this->setTilePosition({this->tilePosition.x - 1, this->tilePosition.y});
    this->flames.emplace_back(this->tilePosition);
    this->collisionBoxes.emplace_back(this->position + Vector{0.0f, this->height - 30.0f}, this->width, 30);
  }

  void FlamethrowerAttack::update()
  {
    this->handleFlameIncrease();
  }

  void FlamethrowerAttack::render() const
  {
    for (const Flame &flame : this->flames)
    {
      flame.render();
    }
  }

}