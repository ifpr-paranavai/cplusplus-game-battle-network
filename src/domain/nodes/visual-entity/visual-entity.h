#pragma once
#include "../entity/entity.h"
#include "../../dto/vector/vector.h"

namespace Game
{
  class VisualEntity : public Entity
  {
  protected:
    float width = 0;
    float height = 0;
    Vector position;

  public:
    virtual void render() const = 0;

    Vector getPosition()
    {
      return this->position;
    }

    int getWidth()
    {
      return this->width;
    }

    int getHeight()
    {
      return this->height;
    }
  };
}