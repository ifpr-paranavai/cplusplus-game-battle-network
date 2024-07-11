#pragma once
#include "../../dtos/render-data/render-data.h"

namespace Game
{
    class RendererPort
    {
    public:
        virtual void renderElement(const RenderDataDTO &renderDataDTO) = 0;
        virtual void updateScreen() = 0;
    };
}
