#include "Timer.h"

Timer::Timer()
{
    SDL_Init(SDL_INIT_TIMER);
    Reset();
}

Uint32 Timer::GetMilliSecondsDelta()
{
    return SDL_GetTicks() - m_milliSecondTicks;
}

Uint32 Timer::GetSecondsDelta()
{
    return GetMilliSecondsDelta() / 1000;
}

void Timer::Reset()
{
    m_milliSecondTicks = SDL_GetTicks();
}
