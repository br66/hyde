#include "Time.hpp"
#include <SDL2-2.0.7\include\SDL.h>
#include <SDL2-2.0.7\include\SDL_video.h>

Tick::Tick()
{
	m_time = 0;
}

Tick::~Tick()
{

}

void Tick::Set(uint32_t tick)
{
	m_time = tick;
}

uint32_t Tick::Time()
{
	return m_time;
}

uint32_t Tick::TimeInMilliseconds()
{
	// still don't understand mod
	return m_time % 1000;
}

uint32_t Tick::TimeInSeconds()
{
	// kinda makes sense
	return m_time / 1000;
}


Timer::Timer()
{
	m_isRunning = false;
	m_hasStopped = false;
	m_hasPaused = false;
	m_hasContinued = false;

	// empty string
	m_name = string();
}

Timer::Timer(string name)
{
	m_isRunning = false;
	m_hasStopped = false;
	m_hasPaused = false;
	m_hasContinued = false;

	m_name = name;
}

Timer::~Timer()
{
	m_name.clear();
}

bool Timer::IsRunning()
{
	return m_isRunning;
}

bool Timer::HasStopped()
{
	return m_hasStopped;
}

bool Timer::HasPaused()
{
	return m_hasPaused;
}

bool Timer::HasContinued()
{
	return m_hasContinued;
}

void Timer::Start()
{
	if (m_isRunning) return;

	m_startTime.Set(SDL_GetTicks());
	m_stoppedTime.Set(0);
	m_pausedTime.Set(0);
	m_continueTime.Set(0);
	
	m_isRunning = true;
	m_hasStopped = false;
	m_hasPaused = false;
	m_hasContinued = false;
}

void Timer::Stop()
{
	if (m_hasStopped) return;

	m_stoppedTime.Set(SDL_GetTicks());
	m_isRunning = false;
	m_hasPaused = false;
	m_hasContinued = false;

	m_hasStopped = true;
}

void Timer::Pause()
{
	if (!m_isRunning || m_hasPaused) return;

	m_isRunning = false;
	m_hasPaused = true;
	m_pausedTime = (SDL_GetTicks() - m_startTime.Time());
}

void Timer::Continue()
{
	if (!m_hasPaused || m_isRunning) return;

	m_isRunning = true;
	m_hasContinued = true;
	m_hasPaused = false;

	m_startTime.Set(SDL_GetTicks() - (m_pausedTime.Time()));
	m_pausedTime.Set(0);
}

void Timer::Restart()
{
	Stop(); Start();
}

string Timer::Name()
{
	return m_name;
}

Tick Timer::RunningTime()
{
	if (m_isRunning)
		return CurrentTime();
	if (m_hasPaused)
		return m_pausedTime;
	if (m_startTime.Time() == 0)
		return m_startTime;
}

Tick Timer::CurrentTime()
{
	Tick temp;
	temp.Set(SDL_GetTicks() - m_startTime.Time());
	return temp;
}