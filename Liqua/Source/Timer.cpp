#include "Liqua.h"
#include "Timer.h"

Liqua::Timer::Timer()
{
	m_Start.QuadPart = 0;
	m_End.QuadPart = 0;
	QueryPerformanceFrequency(&m_Frequency);
}

Liqua::Timer::~Timer()
{

}

void Liqua::Timer::Start()
{
	QueryPerformanceCounter(&m_Start);
}

void Liqua::Timer::End()
{
	QueryPerformanceCounter(&m_End);
}

const float Liqua::Timer::GetTime() const
{
	LARGE_INTEGER time;
	time.QuadPart = m_End.QuadPart - m_Start.QuadPart;

	return (float)LargeIntToSeconds(time);
}

const double Liqua::Timer::LargeIntToSeconds( LARGE_INTEGER& a_LargeInt ) const
{
	//http://cplus.about.com/od/howtodothingsi2/a/timing.htm
	return ((double)a_LargeInt.QuadPart / (double)m_Frequency.QuadPart);
}
