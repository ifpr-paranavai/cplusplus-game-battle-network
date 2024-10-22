#include "date.h"

namespace Game
{
  std::string DateUtil::getCurrentDateTime()
  {
    std::time_t t = std::time(nullptr);
    std::tm* local_time = std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(local_time, "%d/%m/%Y %Hh%M");
    return oss.str();
  }
}
