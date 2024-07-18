#pragma once
#include <iostream>
#include <string_view>
#include "../../utils/math/vector.h"

namespace Game
{
    struct RenderDataDTO
    {
        Vector position;
        int width;
        int height;
        std::string_view hexColor;
    };
}