#pragma once
#include "../../utils/math/vector.h"
#include "../../dtos/render-data/render-data.h"

namespace Game
{
    class RendererPort
    {
    public:
        virtual int getTextHeight(std::string_view text) = 0;
        virtual int getTextWidth(std::string_view text) = 0;
        virtual void renderElement(const RenderDataDTO &renderDataDTO) = 0;
        virtual void renderSprite(const std::string &path, float x, float y, float width, float height) = 0;
        virtual void updateScreen() = 0;
        virtual void renderText(std::string_view text, Vector position) = 0;
        virtual void destroyRenderer() = 0;
    };
}
