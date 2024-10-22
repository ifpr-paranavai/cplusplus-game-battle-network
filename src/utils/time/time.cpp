#include "time.h"

namespace Game
{

  std::string TimeUtil::formatElapsedTime(const float elapsedTime)
  {
    const int totalSeconds = static_cast<int>(elapsedTime);
    const int minutes = totalSeconds / 60;
    const int seconds = totalSeconds % 60;
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << minutes << ':'
        << std::setw(2) << std::setfill('0') << seconds;

    static std::string formattedTime;
    formattedTime = oss.str();
    return formattedTime;
  }

  int TimeUtil::formatedElapsedTimeToInt(const std::string& formatedElapsedTime)
  {
    int hours = std::stoi(formatedElapsedTime.substr(0, 2));
    int minutes = std::stoi(formatedElapsedTime.substr(3, 2));
    return hours * 60 + minutes;
  }

}