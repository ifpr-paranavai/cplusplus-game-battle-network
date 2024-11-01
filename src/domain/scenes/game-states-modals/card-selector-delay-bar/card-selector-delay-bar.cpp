#include "card-selector-delay-bar.h"

namespace Game
{
  void CardSelectorDelayBar::updateDelayTimer()
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

  void CardSelectorDelayBar::updatePercentCompleted()
  {
    this->percentComplete = this->delayTimer / this->delayTime;
    this->loadingBarWidth = this->barWidth * this->percentComplete;
  }

  void CardSelectorDelayBar::renderBorder() const
  {
    Global::adaptersInstance.renderer->renderBorder({this->barPosition,
                                                     this->barWidth,
                                                     this->barHeight,
                                                     Color{0, 0, 0, 255}});
  }

  void CardSelectorDelayBar::renderLoadingBar() const
  {
    Global::adaptersInstance.renderer->renderElement({this->barPosition,
                                                      this->loadingBarWidth,
                                                      this->barHeight,
                                                      this->loadingBarColor});
  }

  void CardSelectorDelayBar::update()
  {
    this->updateDelayTimer();
    this->updatePercentCompleted();
    if (this->percentComplete < 1)
    {
      return;
    }
    this->blingkingBar.update();
  }

  void CardSelectorDelayBar::render() const
  {
    this->renderBorder();
    if (this->percentComplete < 1)
    {
      this->renderLoadingBar();
    }
    else
    {
      this->blingkingBar.render();
      Global::adaptersInstance.textRenderer->renderText({this->helpText, this->textPosition});
    }
  }
}