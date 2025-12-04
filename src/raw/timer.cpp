#include "timer.h"

Timer *Timer::addTimerChild(Object *parent, float interval)
{
    Timer *timer = new Timer();
    timer->interval_ = interval;
    timer->setActive(false); // 默认不启动
    if (parent)
    {
        parent->addChild(timer);
    }
    return timer;
}

void Timer::update(float dt)
{
    timer_ += dt;
    if (timer_ >= interval_)
    {
        timer_ = 0;
        time_out_ = true;
    }
}

bool Timer::timeOut()
{
    if (time_out_)
    {
        time_out_ = false;
        return true;
    }
    return false;
}
