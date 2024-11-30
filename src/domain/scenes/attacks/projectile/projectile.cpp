#include "projectile.h"
#include "../../player/player.h"

namespace Game
{
  Projectile::Projectile(const Vector initialPosition, const int damage) : DynamicAttack(initialPosition)
  {
    this->velocity = {1000, 0};
    this->damage = damage;
    this->width = 30.5;
    this->height = 29.75;
    this->sprites.emplace_back(SpriteConfig{this->width,
                                            this->height,
                                            "assets/sprites/attacks/projectile/0.png",
                                            false,
                                            Vector(0, 0)});
    this->collisionBoxes.emplace_back(this->position, this->width, this->height);
  }

  void Projectile::onCollision(GameObject *other)
  {
    if (dynamic_cast<Player *>(other) || dynamic_cast<Projectile *>(other))
    {
      return;
    }

    this->deleted = true;
  }
}
