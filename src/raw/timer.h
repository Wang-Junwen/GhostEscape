#ifndef TIMER_H
#define TIMER_H

#include "../core/object.h"

class Timer : public Object // 创建时，默认！active
{
protected:
    float timer_ = 0;
    float interval_ = 3.0f; // 默认3秒
    bool time_out_ = false;

public:
    static Timer *addTimerChild(Object *parent, float interval = 3.0f);

    virtual void update(float dt) override;

    void start() { is_active_ = true; }
    void stop() { is_active_ = false; }
    bool timeOut();
    float getProgress() const { return timer_ / interval_; }

    // setter and getter
    void setTimer(float timer) { timer_ = timer; }
    float getTimer() { return timer_; }
    void setInterval(float interval) { interval_ = interval; }
    float getInterval() { return interval_; }
};

#endif // TIMER_H