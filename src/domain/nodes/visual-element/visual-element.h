#pragma once
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../../utils/math/vector.h"
#include "../../../ports/renderer/renderer.h"
#include "../../../utils/color/color.h"

namespace Game
{
    class VisualElement
    {
    protected:
        Vector position;
        float width = 0;
        float height = 0;
        bool flipSpriteHorizontally = false;
        std::string_view hexColor;
        std::string spritePath = "";
        Color spriteColorFilter = {255, 255, 255, 255};

    public:
        VisualElement();
        void renderSprite() const;
        void setConfig(std::string_view hexColor, Vector position, int width, int height);

        void setPosition(Vector position)
        {
            this->position = position;
        }

        void setSpritePath(std::string_view spritePath)
        {
            this->spritePath = spritePath;
        }

        void setFlipSpriteHorizontally(bool flipSpriteHorizontally)
        {
            this->flipSpriteHorizontally = flipSpriteHorizontally;
        }

        void setSpriteColorFilter(Color spriteColorFilter)
        {
            this->spriteColorFilter = spriteColorFilter;
        }
    };
}