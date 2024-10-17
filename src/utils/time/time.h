#pragma once
#include <string>
#include <iomanip>
#include <sstream>

namespace Game
{
  class TimeUtil
  {
  public:
    static std::string formatElapsedTime(const float elapsedTime);
  };
}