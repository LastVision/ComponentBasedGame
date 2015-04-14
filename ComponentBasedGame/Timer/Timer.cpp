#include "Timer.h"


Timer::Timer()
{
	myTimeScale = 1;
}


Timer::~Timer()
{
}

void Timer::Update(LARGE_INTEGER aTotalTime)
{
	if (myRunning == true)
	{
		myPrefFrameTime = myTotalTime;
		myTotalTime = aTotalTime;

		myElapsedTime.Update((static_cast<double>(myTotalTime.QuadPart - myStartTime.QuadPart) / static_cast<double>(myClockFrequency.QuadPart)) * myTimeScale);
		myFrameTime.Update((static_cast<double>(myTotalTime.QuadPart - myPrefFrameTime.QuadPart) / static_cast<double>(myClockFrequency.QuadPart)) * myTimeScale);
	}
	else
	{
		myElapsedTime.Update(0);
		myFrameTime.Update(0);
	}
}

void Timer::Start(LARGE_INTEGER aStartTime, LARGE_INTEGER aClockFrequency)
{
	myClockFrequency = aClockFrequency;
	myStartTime = aStartTime;
	myTotalTime = aStartTime;
	myRunning = true;
}
void Timer::Stop()
{
	myRunning = false;
}

void Timer::Resume(LARGE_INTEGER aCurrentTime)
{
	myPrefFrameTime = myTotalTime;
	myTotalTime = aCurrentTime;

	LARGE_INTEGER timePaused;
	timePaused.QuadPart = myTotalTime.QuadPart - myPrefFrameTime.QuadPart;

	myStartTime.QuadPart += timePaused.QuadPart;

	myRunning = true;
}


void Timer::SetTimeScale(double aTimeScale)
{
	if (aTimeScale < 0.1f)
		myTimeScale = 0.1f;
	else
	{
		myTimeScale = aTimeScale;
	}
}

bool Timer::Running() const
{
	return myRunning;
}

const Time& Timer::GetFrameTime() const
{
	return myFrameTime;
}
const Time& Timer::GetElapsedTime() const
{
	return myElapsedTime;
}