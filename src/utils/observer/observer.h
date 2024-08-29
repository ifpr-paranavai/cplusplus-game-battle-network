#pragma once

namespace Game
{
  template <typename T>
  class Observer
  {
    public:
      virtual void next(const T& value) = 0;
      virtual ~Observer() {}
  };
}
