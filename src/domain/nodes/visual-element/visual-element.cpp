#include "visual-element.h"

namespace Game
{
    VisualElement::VisualElement() {}

    void VisualElement::renderSprite()
    {
        Global::adaptersInstance.renderer->renderElement(RenderDataDTO{
            position = this->position,
            width = this->width,
            height = this->height,
            hexColor = this->hexColor});
    }

    void VisualElement::setConfig(std::string_view hexColor, Vector position, int width, int height)
    {
        this->hexColor = hexColor;
        this->position = position;
        this->width = width;
        this->height = height;
    }

    void VisualElement::setPosition(Vector position)
    {
        this->position = position;
    }
}