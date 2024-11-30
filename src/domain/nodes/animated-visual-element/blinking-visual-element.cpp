#include "blinking-visual-element.h"

namespace Game
{
  BlinkingVisualElement::BlinkingVisualElement(
      const BlinkingVisualElementConfig &config) : firstColor(config.firstColor),
                                                   firstColorDuration(config.firstColorDuration),
                                                   currentColor(config.firstColor),
                                                   secondColor(config.secondColor),
                                                   secondColorDuration(config.secondColorDuration)
  {
    this->position = config.position;
    this->width = config.initialWidth;
    this->height = config.initialHeight;
    this->changeColorTimer.init(this->firstColorDuration);
    this->changeColorTimer.subscribe(&this->changeColorObserver);
  }

  void BlinkingVisualElement::update()
  {
    if (this->changeColorTimer.isFinished())
    {
      const float newDuration = this->currentIsFirstColor() ? this->firstColorDuration : this->secondColorDuration;
      this->changeColorTimer.init(newDuration);
    }
    this->changeColorTimer.update();
  }

  void BlinkingVisualElement::render(const Vector &basePosition) const
  {
    Global::adaptersInstance.renderer->renderElement(RenderElementData{this->position, this->width, this->height, this->currentColor});
  }
}