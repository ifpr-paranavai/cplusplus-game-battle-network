#pragma once
#include "../../../nodes/animated-sprited/animated-sprited.h"
#include "../../../global/global-services/global-services.h"
#include "../../../dto/sound-effect/sound-effect.h"
#include "../../../nodes/tiled-game-object/tiled-game-object.h"

namespace Game
{
  class Flame : public TiledGameObject
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
    void onCollision(GameObject *other) {};

  public:
    Flame(const Vector tilePosition);
    ~Flame();

    void update() override {}

    void render() const override
    {
      this->animatedSprite.renderSprite(this->position);
    }
  };
}