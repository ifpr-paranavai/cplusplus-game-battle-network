#pragma once
#include <list>
#include "../global-adapters/global-adapters.h"
#include "../observer/observer.h"

namespace Game
{
  class TimerSubject
  {
  private:
    std::list<Observer<int> *> observers;
    float elapsedTime = 0;
    float duration = 0;

  public:
    void update()
    {
      if (this->duration == 0)
      {
        return;
      }

      this->elapsedTime += Global::adaptersInstance.timeManager->getDeltaTime();

      if (this->elapsedTime >= this->duration)
      {
        for (Observer<int> *observer : this->observers)
        {
          if (observer == nullptr)
          {
            throw std::runtime_error("Observer is null");
          }

          observer->next(0);
        }
        this->elapsedTime = 0;
        this->duration = 0;
      }
    }

    void init(const float duration)
    {
      this->duration = duration;
      this->elapsedTime = 0;
    }

    void subscribe(Observer<int> *observer)
    {
      observers.push_back(observer);
    }

    void unsubscribe(Observer<int> *observer)
    {
      observers.remove(observer);
    }

    int getDuration() const { return this->duration; }

    bool isFinished() const { return this->duration == 0; }
  };
}
