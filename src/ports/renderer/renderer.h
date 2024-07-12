#pragma once
#include "../../dtos/render-data/render-data.h"

namespace Game
{
    class RendererPort
    {
    public:
        virtual void renderElement(const RenderDataDTO &renderDataDTO) = 0;
        virtual void updateScreen() = 0;
        virtual void renderText(std::string_view text, int x, int y) = 0;
    };
}
