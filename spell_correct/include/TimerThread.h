#ifndef _TIMERTHREAD_H_
#define _TIMERTHREAD_H_

#include "NonCopyable.h"
#include "Thread.h"
#include "Timer.h"
#include <functional>
class TimerThread : private NonCopyable
{
    public:
        typedef std::function<void()> TimerCallback;
        void setTimer(int value, int interval);
        void setTimerCallback(const TimerCallback &);
        void startTimerThread();
        void cancelTimerThread();
    private:
        Timer timer_;
        Thread thread_;
};
#endif /*TIMERTHREAD_H*/ 
