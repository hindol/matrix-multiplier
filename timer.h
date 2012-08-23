#ifndef TIMER_H
#define TIMER_H


#include <ctime>


class Timer
{
public:
    enum TimerState {
        Stopped, Running
    };

    Timer();
    void Start();
    const timespec &Stop();
    const timespec &Peek();

private:
    TimerState state;
    timespec start;
    timespec diff;
};


#endif // TIMER_H
