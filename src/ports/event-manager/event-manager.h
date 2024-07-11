#pragma once
namespace Game
{
    enum class KeyCode
    {
        ARROW_UP = 1,
        ARROW_DOWN = 2,
        ARROW_LEFT = 3,
        ARROW_RIGHT = 4,
    };

    class EventManagerPort
    {
    public:
        virtual bool exitEventIsCalled() = 0;
        virtual bool isKeyPressed(KeyCode keyCode) = 0;
    };
}
