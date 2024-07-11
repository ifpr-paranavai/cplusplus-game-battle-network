#pragma once
#include <iostream>
#include <string_view>

namespace Game
{
    struct RenderDataDTO
    {
        int positionX;
        int positionY;
        int width;
        int height;
        std::string_view hexColor;
    };
}