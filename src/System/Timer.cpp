#include "Timer.h"

Timer::Timer() :
	m_bIsRunning(false)
	, m_dTimeLeft(0)
{

}

void Timer::update(const double delta)
{
	if (m_bIsRunning)
	{
		m_dTimeLeft -= delta;
		if (m_dTimeLeft <= 0)
		{
			m_bIsRunning = false;
			m_callback();
		}
	}
}

void Timer::start(const double duration)
{
	m_dTimeLeft = duration;
	m_bIsRunning = true;
}

void Timer::setCallback(std::function<void()> callback)
{
	m_callback = callback;
}
