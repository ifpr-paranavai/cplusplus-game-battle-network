#pragma once
namespace Game
{
    enum class KeyCode
    {
        ARROW_UP,
        ARROW_DOWN,
        ARROW_LEFT,
        ARROW_RIGHT,
        X
    };

    class KeyboardManagerPort
    {
    public:
        virtual bool exitEventIsCalled() = 0;
        virtual bool isKeyPressed(KeyCode keyCode) = 0;
    };
}
