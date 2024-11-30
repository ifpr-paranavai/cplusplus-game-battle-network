#include "dynamic-game-object.h"

namespace Game
{

  void DynamicGameObject::move()
  {
    float deltaTime = Global::adaptersInstance.timeManager->getDeltaTime();
    if (this->movementTime > 0)
    {
      if (this->movementTimer + deltaTime >= this->movementTime)
      {
        deltaTime = this->movementTime - this->movementTimer;
        this->movementTimer = this->movementTime;
        this->movementFinished = true;
      }
      else
      {
        this->movementTimer += deltaTime;
      }
    }

    this->position += this->velocity * deltaTime;

    if (this->downForce > 0)
    {
      this->velocity.y += this->downForce * deltaTime;
    }
  }

  void DynamicGameObject::update()
  {
    this->move();
  }

}