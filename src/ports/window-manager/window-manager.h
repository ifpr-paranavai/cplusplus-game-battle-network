#pragma once
namespace Game
{
    class WindowManagerPort
    {
    public:
        virtual void createWindow(int width, int height) = 0;
        virtual void destroyWindow() = 0;
    };
}
