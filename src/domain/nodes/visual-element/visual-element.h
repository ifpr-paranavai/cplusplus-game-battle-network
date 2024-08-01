#pragma once
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../../utils/math/vector.h"
#include "../../../dtos/render-data/render-data.h"
#include "../../../ports/renderer/renderer.h"

namespace Game
{
    class VisualElement
    {
    protected:
        Vector position;
        int width = 0;
        int height = 0;
        std::string_view hexColor;

    public:
        VisualElement();
        void renderSprite();
        void setConfig(std::string_view hexColor, Vector position, int width, int height);
        void setPosition(Vector position);
        bool useSprite = false;
    };
}