#pragma once
#include <list>
#include "../visual-entity/visual-entity.h"
#include "../collision-box/collision-box.h"

namespace Game
{
  class GameObject : public VisualEntity
  {
  protected:
    std::list<CollisionBox> collisionBoxes;

    virtual void onCollision(GameObject *other) = 0;

  public:
    virtual void checkCollision(GameObject *other);

    std::list<CollisionBox> getCollisionBoxes()
    {
      return this->collisionBoxes;
    }
  };
}