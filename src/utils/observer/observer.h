#pragma once

namespace Game
{
  class Observer
  {
    public:
      virtual void next() = 0;
      virtual ~Observer() {}
  };
}
