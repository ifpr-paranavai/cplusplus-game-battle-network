#pragma once
#include "../../dto/color/color.h"
#include "../../../utils/timer-subject/timer-subject.h"
#include "../../../utils/observer/observer.h"

namespace Game
{
  struct BlinkingVisualElementConfig
  {
    float initialWidth;
    float initialHeight;
    Color firstColor;
    float firstColorDuration;
    Color secondColor;
    float secondColorDuration;
  };

  class BlinkingVisualElement
  {
  private:
    class ChangeColorObserver : public Observer<int>
    {
    private:
      BlinkingVisualElement &blinkingVisualElement;

    public:
      ChangeColorObserver(BlinkingVisualElement &blinkingVisualElement) : blinkingVisualElement(blinkingVisualElement) {};

      void next(const int &value)
      {
        const bool isFirstColor = blinkingVisualElement.currentColor == blinkingVisualElement.firstColor;
        const float newDuration = isFirstColor ? blinkingVisualElement.secondColorDuration : blinkingVisualElement.firstColorDuration;
        blinkingVisualElement.currentColor = isFirstColor ? blinkingVisualElement.secondColor : blinkingVisualElement.firstColor;
        blinkingVisualElement.changeColorTimer.init(newDuration);
      }
    };

    const Color firstColor;
    const float firstColorDuration;
    const Color secondColor;
    const float secondColorDuration;

    float width;
    float height;
    ChangeColorObserver changeColorObserver = ChangeColorObserver(*this);
    TimerSubject changeColorTimer;
    Color currentColor = this->firstColor;

  public:
    BlinkingVisualElement(const BlinkingVisualElementConfig &config);

    void update();
    void render(const Vector position) const;
  };
}
