#include "visual-element.h"

namespace Game
{
    VisualElement::VisualElement()
    {
    }

    void VisualElement::initSpriteTexture()
    {
        if (this->spritePath != "")
        {
            this->spriteTexture = Global::adaptersInstance.renderer->getSpriteTexture({this->spritePath,
                                                                                       this->width,
                                                                                       this->height,
                                                                                       this->flipSpriteHorizontally,
                                                                                       this->spriteColorFilter});
        }
    }

    void VisualElement::renderSprite() const
    {
        if (this->spritePath != "")
        {
            Global::adaptersInstance.renderer->renderSprite(this->spriteTexture, this->position);
            return;
        }
        Global::adaptersInstance.renderer->renderElement(RenderElementData{
            this->position,
            this->width,
            this->height,
            this->hexColor});
    }

    void VisualElement::setConfig(const VisualElementConfig &config)
    {
        this->hexColor = config.hexColor;
        this->position = config.position;
        this->width = config.width;
        this->height = config.height;
        if (config.spritePath.has_value())
        {
            this->spritePath = config.spritePath.value();
            this->initSpriteTexture();
        }
    }
}