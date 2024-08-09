#pragma once
#include <any>
#include <optional>
#include "../../domain/dto/vector/vector.h"
#include "../../domain/dto/color/color.h"
#include "../../domain/dto/sprite-texture/sprite-texture.h"

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

    struct RenderSpriteData2
    {
        std::string_view path;
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
        virtual void renderSprite(const SpriteTexture &spriteTexture, Vector position) = 0;
        virtual void updateScreen() = 0;
        virtual void renderText(std::string_view text, Vector position) = 0;
        virtual void destroyRenderer() = 0;
        virtual SpriteTexture getSpriteTexture(const RenderSpriteData2 &renderSpriteData) = 0;
    };
}
