#include "dynamic-body.h"

namespace Game
{
    DynamicBody::DynamicBody(int width, int height) : Element(width, height) {}

    void DynamicBody::move()
    {
        const float deltaTime = Global::adaptersInstance.timeManager->getDeltaTime();
        this->position += this->velocity * deltaTime;
    }
}