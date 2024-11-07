#pragma once
#include "../visual-entity/visual-entity.h"
#include "../../dto/color/color.h"
#include "../../../utils/timer-subject/timer-subject.h"
#include "../../../utils/observer/observer.h"

namespace Game
{
  struct BlinkingVisualElementConfig
  {
    const Vector position;
    const int initialWidth;
    const int initialHeight;
    const Color firstColor;
    const float firstColorDuration;
    const Color secondColor;
    const float secondColorDuration;
  };

  class BlinkingVisualElement : public VisualEntity
  {
  private:
    class ChangeColorObserver : public Observer<int>
    {
    private:
      BlinkingVisualElement &blinkingVisualElement;

    public:
      ChangeColorObserver(BlinkingVisualElement &blinkingVisualElement) : blinkingVisualElement(blinkingVisualElement) {};

      void next(const int &value) override
      {
        const bool isFirstColor = blinkingVisualElement.currentIsFirstColor();
        const float newDuration = isFirstColor ? blinkingVisualElement.secondColorDuration : blinkingVisualElement.firstColorDuration;
        blinkingVisualElement.currentColor = isFirstColor ? blinkingVisualElement.secondColor : blinkingVisualElement.firstColor;
      }
    };

    const Color firstColor;
    const float firstColorDuration;
    const Color secondColor;
    const float secondColorDuration;

    float peddingNewDuration = 0;
    ChangeColorObserver changeColorObserver = ChangeColorObserver(*this);
    TimerSubject changeColorTimer;
    Color currentColor;

    bool currentIsFirstColor() { return this->currentColor == this->firstColor; }

  public:
    BlinkingVisualElement(const BlinkingVisualElementConfig &config);

    void update() override;
    void render() const override;
  };
}