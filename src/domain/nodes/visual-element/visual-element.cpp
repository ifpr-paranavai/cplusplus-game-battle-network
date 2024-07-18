#include "visual-element.h"

namespace Game
{
    VisualElement::VisualElement(RendererPort *_renderer) : renderer(_renderer) {}

    void VisualElement::renderSprite()
    {
        this->renderer->renderElement(RenderDataDTO{
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