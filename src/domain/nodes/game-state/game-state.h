#pragma once
#include <array>
#include "../sprite/sprite.h"
#include "../../../config/config.h"

namespace Game
{
  class GameState
  {
    const std::array<Sprite, 2> backgroundSprites = {
        Sprite({Config::WINDOW_WIDTH,
                Config::WINDOW_HEIGHT,
                "assets/sprites/background/bg.png",
                false,
                Vector(0, 0)}),
        Sprite({Config::WINDOW_WIDTH,
                Config::WINDOW_HEIGHT,
                "assets/sprites/background/clouds.png",
                false,
                Vector(0, 0)})};

  public:
    virtual void render()
    {
      for (const auto bg : this->backgroundSprites)
      {
        bg.renderSprite(Vector(0, 0));
      }
    }
  };
}