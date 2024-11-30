#include "game-object.h"

namespace Game
{
  void GameObject::checkCollision(GameObject *other)
  {
    if (!other)
    {
      throw std::invalid_argument("other is null");
    }

    for (auto &collisionBox : this->collisionBoxes)
    {
      for (auto &collisionBox2 : other->getCollisionBoxes())
      {
        if (collisionBox.collidesWith(collisionBox2))
        {
          this->onCollision(other);
        }
      }
    }
  }
}