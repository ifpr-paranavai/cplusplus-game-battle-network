#pragma once
#include "../../../dtos/render-data/render-data.h"
#include "../../../ports/renderer/renderer.h"

namespace Game
{
    class VisualElement
    {
    protected:
        int positionX = 0;
        int positionY = 0;
        int width = 0;
        int height = 0;
        std::string_view hexColor;
        RendererPort *renderer;

    public:
        VisualElement(RendererPort *_renderer);
        void renderSprite();
        void setConfig(std::string_view hexColor, int positionX, int positionY, int width, int height);
        void setPosition(int positionX, int positionY);
    };
}