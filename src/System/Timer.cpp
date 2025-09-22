#include "Timer.h"

CTimer::CTimer() :
	m_bIsRunning(false)
	, m_dTimeLeft(0)
{

}

void CTimer::update(const double delta)
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

void CTimer::start(const double duration)
{
	m_dTimeLeft = duration;
	m_bIsRunning = true;
}

void CTimer::setCallback(std::function<void()> callback)
{
	m_callback = callback;
}
