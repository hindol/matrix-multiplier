#include "timer.h"


Timer::Timer() : state(Stopped) {}

void Timer::Start()
{
    state = Running;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
}

const timespec &Timer::Stop()
{
    Peek(); // Updates diff
    state = Stopped;
    return diff;
}

const timespec &Timer::Peek()
{
    if (state == Running)
    {
        clock_gettime(CLOCK_MONOTONIC_RAW, &diff);

        if ((diff.tv_nsec - start.tv_nsec) < 0)
        {
            diff.tv_sec = diff.tv_sec - start.tv_sec - 1;
            diff.tv_nsec = 1000000000 + diff.tv_nsec - start.tv_nsec;
        } else {
            diff.tv_sec = diff.tv_sec - start.tv_sec;
            diff.tv_nsec = diff.tv_nsec - start.tv_nsec;
        }
    }

    return diff;
}
