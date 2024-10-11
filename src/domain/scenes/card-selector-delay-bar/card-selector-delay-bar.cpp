#include "card-selector-delay-bar.h"

namespace Game
{

  void CardSelectorDelayBar::update()
  {
    if (this->delayTimer >= this->delayTime)
    {
      return;
    }

    this->delayTimer += Global::adaptersInstance.timeManager->getDeltaTime();
    if (this->delayTimer >= this->delayTime)
    {
      this->delayTimer = this->delayTime;
      this->onCompleteLoadSubject.next(this->delayTimer);
    }
  }

  void CardSelectorDelayBar::render()
  {
    Global::adaptersInstance.renderer->renderBorder({this->barPosition,
                                                     this->barWidth,
                                                     this->barHeight,
                                                     Color{0, 0, 0, 255}});
    const float percentComplete = this->delayTimer / this->delayTime;
    const float loadingBarWidth = this->barWidth * percentComplete;
    Global::adaptersInstance.renderer->renderElement({this->barPosition,
                                                      loadingBarWidth,
                                                      this->barHeight,
                                                      Color{239, 184, 16, 255}});

    if (percentComplete == 1)
    {
      Global::adaptersInstance.textRenderer->renderText({this->helpText, this->textPosition});
    }
  }
}