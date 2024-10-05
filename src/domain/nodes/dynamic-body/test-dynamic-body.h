#include "./dynamic-body.h"
#include "../../../utils/unit-test/unit-test.h"
#include "../../../ports/time-manager/time-manager.h"

namespace Test
{
  class DynamicBodyChild : public Game::DynamicBody
  {
  public:
    DynamicBodyChild(int width, int height) : Game::DynamicBody(width, height)
    {
      this->position = {0, 0};
      this->velocity = {10, 10};
    }

    void onCollision(Game::Element *other) override {}

    void update() override {}
  };

  class TimeManagerAdapter : public Game::TimeManagerPort
  {
  private:
    float lastTime = 0;
    float deltaTime;

  public:
    void updateTime() override
    {
      this->lastTime += 1;
      this->deltaTime = 1;
    }

    float getDeltaTime() override
    {
      return this->deltaTime;
    }
  };

  class TestDynamicBody : public UnitTest
  {

  private:
    DynamicBodyChild dynamicBody = DynamicBodyChild(10, 10);

    void testMove()
    {
      ASSERT(dynamicBody.getPosition().x == 0);
      ASSERT(dynamicBody.getPosition().y == 0);
      Game::Global::adaptersInstance.timeManager->updateTime();
      dynamicBody.move();
      ASSERT(dynamicBody.getPosition().x == 10);
      ASSERT(dynamicBody.getPosition().y == 10);
    }

    void init()
    {
      Game::Global::adaptersInstance.timeManager = new TimeManagerAdapter();
    }

  public:
    void run() override
    {
      this->init();
      this->testMove();
    }
  };
}