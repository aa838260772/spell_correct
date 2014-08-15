#ifndef _TIMER_H_
#define _TIMER_H_

#include "NonCopyable.h"
#include <sys/timerfd.h>
#include <functional>

class Timer : private NonCopyable
{
    public:
        typedef std::function<void()> TimerCallback;
        Timer();
        ~Timer();
        void setTimer(int val, int interval);
        void setTimerCallback(const TimerCallback &);
        void runTimer();
        void cancelTimer();
    private:
        int timerfd_;
        struct itimerspec howlong_; 
        TimerCallback timercallback_;
        bool isstarted_;
};
#endif /*TIMER_H*/ 
