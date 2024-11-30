#pragma once
#include <cstdint>

namespace Game
{
    struct Color
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;

        bool operator==(const Color &other) const
        {
            return (
                this->r == other.r &&
                this->g == other.g &&
                this->b == other.b &&
                this->a == other.a);
        }
    };

}