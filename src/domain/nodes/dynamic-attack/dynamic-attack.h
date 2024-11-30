#pragma once
#include <list>
#include "../collision-box/collision-box.h"
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../dto/vector/vector.h"
#include "../../../config/config.h"
#include "../dynamic-game-object/dynamic-game-object.h"
#include "../sprite/sprite.h"

namespace Game
{
  class DynamicAttack : public DynamicGameObject
  {
  protected:
    std::list<Sprite> sprites;
    bool deleted = false;
    int damage;

  public:
    DynamicAttack(Vector initialPosition);
    virtual ~DynamicAttack();
    void update() override;
    void render(const Vector &basePosition = {0, 0}) const override;
    inline bool isDeleted() const { return this->deleted; }
    inline int getDamage() const { return this->damage; }
  };
}