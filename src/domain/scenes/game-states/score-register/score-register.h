#pragma once
#include <string>
#include "../../../nodes/game-state/game-state.h"
#include "../../../../utils/global-adapters/global-adapters.h"
#include "../../../../config/config.h"
#include "../../../dto/vector/vector.h"
#include "../../../styles/colors.h"

namespace Game
{
  class ScoreRegister : public GameState
  {
  private:
    void verifyCommands();
    void renderForm();

  public:
    int selectedLetterIndex = 0;
    char playerNameLetters[3] = {'A', 'A', 'A'};
    const int letterYPosition = Config::WINDOW_HEIGHT / 2 - Global::adaptersInstance.textRenderer->getTextHeight("A") / 2;
    const int letterWidth = Global::adaptersInstance.textRenderer->getTextWidth("A");
    const int initialLetterXPosition = Config::WINDOW_WIDTH / 2 - this->letterWidth / 2 - this->letterWidth;

    void render() override;
  };
}