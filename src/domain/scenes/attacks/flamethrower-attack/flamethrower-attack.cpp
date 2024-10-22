#include "flamethrower-attack.h"

namespace Game
{

  FlamethrowerAttack::FlamethrowerAttack(Vector elementPosition) : TileBasedAttack(60, 80)
  {
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
    this->collisionBoxes.emplace_back(this->position + Vector{0, this->height - 30}, this->width, 30);
  }

  void FlamethrowerAttack::update()
  {
    this->handleFlameIncrease();
  }

  void FlamethrowerAttack::render()
  {
    for (Flame &flame : this->flames)
    {
      flame.renderSprite();
    }
  }

  void FlamethrowerAttack::onCollision(Element *other)
  {
  }

}