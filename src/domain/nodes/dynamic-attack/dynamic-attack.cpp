#include "dynamic-attack.h"

namespace Game
{
  DynamicAttack::DynamicAttack(
      Vector initialPosition) : DynamicBody(10, 10)
  {
    this->velocity = {1000, 0};
    this->position = initialPosition;
    this->collisionBoxes.emplace_back(this->position, this->width, this->height);
  }

  DynamicAttack::~DynamicAttack()
  {
    for (Sprite &sprite : this->sprites)
    {
      sprite.destroy();
    }
  }

  void DynamicAttack::update()
  {
    if (this->position.x > Config::WINDOW_WIDTH || this->position.x < 0 || this->position.y > Config::WINDOW_HEIGHT || this->position.y < 0)
    {
      this->deleted = true;
    }
    for (CollisionBox &collisionBox : this->collisionBoxes)
    {
      collisionBox.setPosition(this->position);
    }
  }

  void DynamicAttack::render()
  {
    for (const Sprite &sprite : this->sprites)
    {
      sprite.renderSprite(this->position);
    }
  }

}