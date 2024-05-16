#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include"Settings.h"

class Timer
{
public:
    Timer();
    ~Timer(){;}

    void Start();
    void Reset();
    void Restart();
    void Pause();
    void Unpaused();
    uint32_t Getticks();

    bool isStarted();
    bool isPaused();

private:
    uint32_t StartTicks;	 //Ticks since start
    uint32_t  PausedTicks;   //Ticks since stop

    bool Paused;
    bool Started;
};

#endif // TIMER_H_INCLUDED
