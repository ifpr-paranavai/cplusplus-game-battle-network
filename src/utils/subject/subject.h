#pragma once
#include <vector>
#include "../observer/observer.h"

namespace Game {
  class Subject
  {
    private:
      std::vector<Observer*> observers;

    public:
      void subscribe(Observer *observer)
      {
        observers.push_back(observer);
      }

      void unsubscribe(Observer *observer)
      {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
      } 

      void next()
      {
        for (auto observer : observers)
        {
          observer->next();
        }
      }
  };
}
