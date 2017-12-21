/**********************************************************************************************//**
 * @file	time.hpp
 * @author	br66
 * @date	12/21/17
 * @brief	This feature allows the game to have timers, measured in milliseconds.
 **************************************************************************************************/
#ifndef _TIME_HPP_
#define _TIME_HPP_

#include <string>
using namespace std;

class Tick
{
public:
	Tick();
	~Tick();
	void Set(uint32_t tick);
	uint32_t Time();
	uint32_t TimeInMilliseconds();
	uint32_t TimeInSeconds();

private:
	uint32_t m_time;
};

class Timer
{
public:
	Timer();

	// Gives the timer a name, useful if an object has more than one timer.
	Timer(string name);

	~Timer();

	bool IsRunning();
	bool HasStopped();
	bool HasPaused();
	// For the rare instance that whether the timer resumed from a paused is needed.
	bool HasContinued();

	void Start();
	void Stop();
	void Pause();
	void Continue();
	void Restart();

	string Name();

	// Time difference between when the timer first started and when it last ran
	Tick RunningTime(); 
	// Time difference between when the timer first started to now
	Tick CurrentTime();

private:
	bool m_isRunning;
	bool m_hasStopped;
	bool m_hasPaused;
	bool m_hasContinued;

	Tick m_startTime;
	Tick m_stoppedTime;
	Tick m_continueTime;
	Tick m_pausedTime;

	string m_name;
};

#endif
