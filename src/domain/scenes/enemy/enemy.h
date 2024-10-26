#pragma once
#include <string>
#include <random>
#include <ctime>
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../../utils/log-manager/log-manager.h"
#include "../../global/global-services/global-services.h"
#include "../../nodes/actor/actor.h"

namespace Game
{
  enum class Direction
  {
    UP,
    DOWN,
    LEFT,
    RIGHT
  };

  class Enemy : public Actor
  {
  private:
    float movementDecisionTimer = 0;
    float attackTimer = 0;
    bool dead = false;
    Subject<GameObject *> onCollide;

    void handleMovement();
    void handleAttack();
    bool tryMove(Direction direction);
    Direction getRandomDirection();
    void moveRandomlyWithinLimits();

  protected:
    float movementDecisionTime = 0.5;
    float attackTime = 1;
    bool canMove = true;
    bool canAttack = true;

    virtual void attack() = 0;
    void onCollision(GameObject *other) override;

  public:
    Enemy();
    void update() override;
    void render() const override;
  };
}