#pragma once
#include <string_view>
#include "../../../config/config.h"
#include "../../dto/vector/vector.h"
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../dto/color/color.h"
#include "../../../utils/subject/subject.h"
#include "../../../utils/observer/observer.h"

namespace Game
{
  class CardSelectorDelayBar
  {
  private:
    const float barWidth = Config::WINDOW_WIDTH / 2;
    const float barHeight = 30;
    const Vector barPosition = Vector(this->barWidth / 2, 10);
    const std::string_view helpText = "Pressione Z";
    const Vector textPosition = this->barPosition + Vector((this->barWidth - Global::adaptersInstance.renderer->getTextWidth(helpText)) / 2, 0);
    Subject<int> onCompleteLoadSubject;
    const float delayTime = 10;
    float delayTimer = 0;

  public:
    void update();
    void render();

    void subscribeToOnCompleteLoad(Observer<int> *observer)
    {
      this->onCompleteLoadSubject.subscribe(observer);
    }

    void resetTimer()
    {
      this->delayTimer = 0;
    }
  };
}