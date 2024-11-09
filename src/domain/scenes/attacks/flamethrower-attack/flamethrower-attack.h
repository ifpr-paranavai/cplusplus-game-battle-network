#pragma once
#include <list>
#include "../../../nodes/tile-based-attack/tile-based-attack.h"
#include "../../../../utils/global-adapters/global-adapters.h"
#include "../../../nodes/sprite/sprite.h"
#include "../flame/flame.h"

namespace Game
{

  class FlamethrowerAttack : public TileBasedAttack
  {
  private:
    float increaseFlameTime = 0.5;
    float increaseFlameTimer = 0;
    std::list<Flame> flames;

    void handleFlameIncrease();
    void increaseFlame();

  protected:
    void onCollision(GameObject *other) {}

  public:
    FlamethrowerAttack(Vector initialTilePoition);

    void update() override;
    void render(const Vector &basePosition = {0, 0}) const override;
  };
}