#pragma once

namespace Game
{
    class CollisionBox
    {
    private:
        int positionX;
        int positionY;
        int width;
        int height;

    public:
        CollisionBox(int positionX, int positionY, int with, int height);
        void setPosition(int positionX, int positionY);
        bool collidesWith(CollisionBox *other);
        int getPositionX();
        int getPositionY();
        int getWidth();
        int getHeight();
    };
}
