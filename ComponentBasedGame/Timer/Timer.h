#pragma once
#include <Windows.h>
#include "Time.h"

class Timer
{
public:
	Timer();
	~Timer();

	void Update(LARGE_INTEGER aTotalTime);

	void Start(LARGE_INTEGER aStartTime, LARGE_INTEGER aClockFrequency);
	void Stop();
	void Resume(LARGE_INTEGER aCurrentTime);
	void SetTimeScale(double aScale);
	bool Running() const;

	const Time& GetFrameTime() const;
	const Time& GetElapsedTime() const;

private:

	bool myRunning;

	Time myElapsedTime;
	Time myFrameTime;

	LARGE_INTEGER myClockFrequency;
	LARGE_INTEGER myStartTime;
	LARGE_INTEGER myTotalTime;
	LARGE_INTEGER myPrefFrameTime;

	double myTimeScale;
};

