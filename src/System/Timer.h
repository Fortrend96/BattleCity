#pragma once

#include <functional>

class CTimer
{
public:
	CTimer();

	void update(const double delta);
	void start(const double duration);
	void setCallback(std::function<void()> callback);

private:
	std::function<void()> m_callback;
	double m_dTimeLeft;
	bool m_bIsRunning;

};
