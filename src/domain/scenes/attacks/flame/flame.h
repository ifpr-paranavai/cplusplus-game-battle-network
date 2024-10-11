#pragma once
#include "../../../nodes/tile-based-attack/tile-based-attack.h"
#include "../../../nodes/animated-sprited/animated-sprited.h"
#include "../../../global/global-services/global-services.h"
#include "../../../dto/sound-effect/sound-effect.h"

namespace Game
{
  class Flame : public TileBasedBody
  {
  private:
    AnimatedSprite animatedSprite = AnimatedSprite({0.2f,
                                                    "assets/sprites/attacks/fire",
                                                    8,
                                                    this->width,
                                                    this->height,
                                                    false,
                                                    Vector(0, 0)});
    const SoundEffect flameSFX = Global::adaptersInstance.audioManager->initSoundEffect("assets/sounds/flame.wav");

  protected:
    void onCollision(Element *other) {};

  public:
    Flame(const Vector tilePosition);
    ~Flame();

    void renderSprite() const
    {
      this->animatedSprite.renderSprite(this->position);
    }
  };
}