#pragma once

namespace Game
{
    class TimeManagerPort
    {
    public:
        virtual float getDeltaTime() = 0;
        virtual void updateTime() = 0;
    };
}