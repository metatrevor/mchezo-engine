#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>

class Timer
{
    public:
        Timer();
        ~Timer(){}
        //Get MilliSeconds elaspsed since Reset()
        Uint32 GetMilliSecondsDelta();
        //Get Seconds elapsed since Reset()
        Uint32 GetSecondsDelta();
        void Reset();

    private:
        Uint32 m_milliSecondTicks;

};

#endif // TIMER_H
