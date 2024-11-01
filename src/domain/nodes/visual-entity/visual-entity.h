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

    void setPosition(const Vector position)
    {
      this->position = position;
    }

    Vector getPosition() const
    {
      return this->position;
    }

    int getWidth() const
    {
      return this->width;
    }

    int getHeight() const
    {
      return this->height;
    }
  };
}