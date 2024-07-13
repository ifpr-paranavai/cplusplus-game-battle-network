#include "log-manager.h"

namespace Game
{

    void LogManager::log(std::string_view message)
    {
        if (Config::DEBUG)
        {
            std::cout << message << std::endl;
        }
    }
}