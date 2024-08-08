#pragma once
#include <optional>
#include "../../utils/math/vector.h"
#include "../../utils/color/color.h"

namespace Game
{

    struct RenderElementData
    {
        Vector position;
        float width;
        float height;
        std::string_view hexColor;
    };

    struct RenderSpriteData
    {
        std::string path;
        float x;
        float y;
        float width;
        float height;
        bool flipHorizontal;
        std::optional<Color> colorFilter;
    };

    class RendererPort
    {
    public:
        virtual int getTextHeight(std::string_view text) = 0;
        virtual int getTextWidth(std::string_view text) = 0;
        virtual void renderElement(const RenderElementData &renderDataDTO) = 0;
        virtual void renderSprite(const RenderSpriteData &renderSpriteData) = 0;
        virtual void updateScreen() = 0;
        virtual void renderText(std::string_view text, Vector position) = 0;
        virtual void destroyRenderer() = 0;
    };
}
