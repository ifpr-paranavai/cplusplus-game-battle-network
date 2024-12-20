#pragma once
#include <array>
#include <optional>
#include <any>
#include "../sprite/sprite.h"
#include "../../../config/config.h"
#include "../visual-entity/visual-entity.h"

namespace Game
{
  template <typename Params>
  struct GameStateRouteParams
  {
    Params data;
  };

  using DefaultRouteParams = std::optional<GameStateRouteParams<std::any>>;

  class GameState : public VisualEntity
  {
  private:
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

  protected:
    DefaultRouteParams params;

  public:
    GameState(DefaultRouteParams _params = std::nullopt) : params(_params) {}

    virtual void render(const Vector &basePosition = {0, 0}) const
    {
      for (const auto bg : this->backgroundSprites)
      {
        bg.render(Vector(0, 0));
      }
    }
  };
}