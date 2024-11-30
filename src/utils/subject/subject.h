#pragma once
#include <list>
#include "../observer/observer.h"

namespace Game
{
  template <typename T>
  class Subject
  {
  private:
    std::list<Observer<T> *> observers;

  public:
    inline void subscribe(Observer<T> *observer) { observers.push_back(observer); }
    inline void unsubscribe(Observer<T> *observer) { observers.remove(observer); }

    void next(const T &value)
    {
      for (auto observer : observers)
      {
        observer->next(value);
      }
    }
  };
}
