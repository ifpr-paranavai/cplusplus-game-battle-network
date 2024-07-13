#pragma once
#include <iostream>
#include "../../config/config.h"

namespace Game
{
    class LogManager
    {
    public:
        static void log(std::string_view message);
    };
}