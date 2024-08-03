#include "visual-element.h"

namespace Game
{
    VisualElement::VisualElement() {}

    void VisualElement::renderSprite() const
    {
        if (this->spritePath != "")
        {
            Global::adaptersInstance.renderer->renderSprite(
                this->spritePath,
                this->position.x,
                this->position.y,
                this->width,
                this->height,
                this->flipSpriteHorizontally);
            return;
        }
        Global::adaptersInstance.renderer->renderElement(RenderDataDTO{
            this->position,
            this->width,
            this->height,
            this->hexColor});
    }

    void VisualElement::setConfig(std::string_view hexColor, Vector position, int width, int height)
    {
        this->hexColor = hexColor;
        this->position = position;
        this->width = width;
        this->height = height;
    }
}