#pragma once
#include <string_view>
#include "../../nodes/game-state-modal/game-state-modal.h"

namespace Game
{
  class Pause : public GameStateModal
  {
  private:
    static constexpr std::string_view title = "Pausado";

  public:
    void update() override;
    void render() const override;
  };
}
