#include "collision-box.h"

namespace Game
{
    CollisionBox::CollisionBox(const Vector _position, const int _width, const int _height) : position(_position),
                                                                                              width(_width),
                                                                                              height(_height)
    {
    }

    void CollisionBox::renderCollisionBox() const
    {
        Global::adaptersInstance.renderer->renderBorder({
            {this->position.x, this->position.y},
            this->width,
            this->height,
            Color{0, 0, 0, 255},
        });
    }

    bool CollisionBox::collidesWith(const CollisionBox &other)
    {
        Vector otherPosition = other.getPosition();

        return (this->position.x < otherPosition.x + other.getWidth() &&
                this->position.x + width > otherPosition.x &&
                this->position.y < otherPosition.y + other.getHeight() &&
                this->position.y + height > otherPosition.y);
    }
}