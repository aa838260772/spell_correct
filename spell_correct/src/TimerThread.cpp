#include "TimerThread.h"
using namespace std;

void TimerThread::setTimer(int val, int interval)
{
timer_.setTimer(val, interval);
}

void TimerThread::setTimerCallback(const TimerCallback &cb)
{
timer_.setTimerCallback(cb);
thread_.setCallback(bind(&Timer::runTimer, &timer_));
}

void TimerThread::startTimerThread()
{
thread_.start();
}

void TimerThread::cancelTimerThread()
{
//thread_.join();
timer_.cancelTimer();
}
