#pragma once
#include "../game-object/game-object.h"

namespace Game
{
  class DynamicGameObject : public GameObject
  {
  private:
    void move();

  protected:
    float downForce = 0;
    float movementTime = 0;
    float movementTimer = 0;
    bool movementFinished = false;
    Vector velocity = {0, 0};

  public:
    void update() override;
  };
}