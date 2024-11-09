#pragma once
#include "../entity/entity.h"
#include "../../dto/vector/vector.h"

namespace Game
{
  class VisualEntity : public Entity
  {
  protected:
    int width = 0;
    int height = 0;
    Vector position;

  public:
    virtual void render(const Vector &basePosition = {0, 0}) const = 0;
    inline void setPosition(const Vector &position) { this->position = position; }
    inline const Vector &getPosition() const { return this->position; }
    inline void setWidth(const int width) { this->width = width; }
    inline int getWidth() const { return this->width; }
    inline void setHeight(const int height) { this->height = height; }
    inline int getHeight() const { return this->height; }
  };
}