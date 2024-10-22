#pragma once
#include <any>

namespace Game
{
    struct SpriteTexture
    {
        std::any data;
        float width;
        float height;
        bool flipHorizontally;
        bool flipVertically = false;
    };
}