#pragma once
#include "../../../nodes/tile-based-attack/tile-based-attack.h"

// TODO: TileBasedAttack without render?
namespace Game
{
  class Stab : public TileBasedAttack
  {
  private:
    bool isColliding = false;

  protected:
    void onCollision(GameObject *other) override
    {
      this->isColliding = true;
    }

  public:
    Stab(const Vector swordTilePosition, const int damage);

    void makeAsDeleted()
    {
      this->deleted = true;
    }

    void update() override
    {
      if (this->isColliding)
      {
        this->damage = 0;
      }
    }

    void render(const Vector &basePosition = {0, 0}) const override {}
  };
}