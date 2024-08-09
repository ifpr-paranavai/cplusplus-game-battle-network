#pragma once
#include <optional>
#include <string_view>
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../dto/vector/vector.h"
#include "../../../ports/renderer/renderer.h"
#include "../../dto/color/color.h"

namespace Game
{

    struct VisualElementConfig
    {
        std::string_view hexColor;
        Vector position;
        float width;
        float height;
        std::optional<std::string_view> spritePath;
    };

    class VisualElement
    {
    private:
        SpriteTexture spriteTexture;
        Vector position;
        float width = 0;
        float height = 0;
        bool flipSpriteHorizontally = false;
        std::string_view hexColor;
        std::string_view spritePath = "";
        Color spriteColorFilter = {255, 255, 255, 255};

        void initSpriteTexture();

    public:
        VisualElement();
        void renderSprite() const;
        void setConfig(const VisualElementConfig &config);

        void setPosition(Vector position)
        {
            this->position = position;
        }

        void setSpritePath(std::string_view spritePath)
        {
            this->spritePath = spritePath;
            this->initSpriteTexture();
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