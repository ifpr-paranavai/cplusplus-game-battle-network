#include "blinking-visual-element.h"

namespace Game
{
  BlinkingVisualElement::BlinkingVisualElement(
      const BlinkingVisualElementConfig &config) : width(config.initialWidth),
                                                   height(config.initialHeight),
                                                   firstColor(config.firstColor),
                                                   firstColorDuration(config.firstColorDuration),
                                                   secondColor(config.secondColor),
                                                   secondColorDuration(config.secondColorDuration)
  {
    this->changeColorTimer.init(this->firstColorDuration);
    this->changeColorTimer.subscribe(&this->changeColorObserver);
  }

  void BlinkingVisualElement::update()
  {
    this->changeColorTimer.update();
  }

  void BlinkingVisualElement::render(const Vector position) const
  {
    Global::adaptersInstance.renderer->renderElement(RenderElementData{position, this->width, this->height, this->currentColor});
  }
}