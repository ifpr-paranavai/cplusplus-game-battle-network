#include "visual-element.h"

namespace Game
{
    VisualElement::VisualElement(RendererPort *_renderer) : renderer(_renderer) {}

    void VisualElement::renderSprite()
    {
        this->renderer->renderElement(RenderDataDTO{
            positionX = this->positionX,
            positionY = this->positionY,
            width = this->width,
            height = this->height,
            hexColor = this->hexColor});
    }

    void VisualElement::setConfig(std::string_view hexColor, int positionX, int positionY, int width, int height)
    {
        this->hexColor = hexColor;
        this->positionX = positionX;
        this->positionY = positionY;
        this->width = width;
        this->height = height;
    }

    void VisualElement::setPosition(int positionX, int positionY)
    {
        this->positionX = positionX;
        this->positionY = positionY;
    }
}