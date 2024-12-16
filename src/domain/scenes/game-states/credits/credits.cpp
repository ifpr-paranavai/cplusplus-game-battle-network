#include "credits.h"

namespace Game
{
  void CreditsState::verifyCommands()
  {
    if (Global::adaptersInstance.keyboardManager->isKeyPressed(KeyCode::ENTER))
    {
      this->backOption.click();
    }
  }

  void CreditsState::render(const Vector &basePosition) const
  {
    GameState::render(basePosition);
    Global::adaptersInstance.textRenderer->renderText({this->title, this->titlePosition, this->titleFontSize});
    Global::adaptersInstance.textRenderer->renderText({this->creditsText,
                                                       this->creditsPosition,
                                                       this->creditsTextFontSize,
                                                       this->creditsMaxWidth});
    this->backOption.render();
  }
}