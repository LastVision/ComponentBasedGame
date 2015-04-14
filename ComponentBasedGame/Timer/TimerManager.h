#pragma once

#include <windows.h>
#include "Timer.h"
#include <vector>
#include "Time.h"

class TimerManager
{
public:
	TimerManager();
	~TimerManager();

	void Update();
	void StartAll();
	void StopAll();
	void ResumeAll();

	void Start(int aID);
	void Stop(int aID);
	void Resume(int aID);

	const Time& MasterTotalTime() const;
	const Time& MasterFrameTime() const;

	int CreateTimer();
	Timer& GetTimer(int aID);

	const LARGE_INTEGER GetTotalTime() const;
	const LARGE_INTEGER GetFrequency() const;

private:
	LARGE_INTEGER myTime;
	LARGE_INTEGER myClockFrequency;
	std::vector<Timer> myTimers;

	Timer myMasterTimer;
};

