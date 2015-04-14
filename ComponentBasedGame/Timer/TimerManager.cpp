#include "TimerManager.h"
#include <assert.h>
#include <iostream>


TimerManager::TimerManager()
{
	QueryPerformanceFrequency(&myClockFrequency);
	QueryPerformanceCounter(&myTime);

	myMasterTimer.Start(myTime, myClockFrequency);
}


TimerManager::~TimerManager()
{
}

void TimerManager::Update()
{
	QueryPerformanceCounter(&myTime);

	myMasterTimer.Update(myTime);

	for (unsigned int i = 0; i < myTimers.size(); i++)
	{
		myTimers[i].Update(myTime);
	}
}

void TimerManager::StartAll()
{
	for (unsigned int i = 0; i < myTimers.size(); i++)
	{
		myTimers[i].Start(myTime, myClockFrequency);
	}
}

void TimerManager::StopAll()
{
	for (unsigned int i = 0; i < myTimers.size(); i++)
	{
		myTimers[i].Stop();
	}
}

void TimerManager::ResumeAll()
{
	for (unsigned int i = 0; i < myTimers.size(); i++)
	{
		myTimers[i].Resume(myTime);
	}
}

void TimerManager::Start(int aID)
{
	assert(aID >= 0 && "timerID smaller than 0");
	assert(static_cast<unsigned int>(aID) <= myTimers.size() && "timerID larger than myTimers.size()");
	myTimers[aID].Start(myTime, myClockFrequency);
}

void TimerManager::Stop(int aID)
{
	assert(aID >= 0 && "timerID smaller than 0");
	assert(static_cast<unsigned int>(aID) <= myTimers.size() && "timerID larger than myTimers.size()");
	myTimers[aID].Stop();
}

void TimerManager::Resume(int aID)
{
	assert(aID >= 0 && "timerID smaller than 0");
	assert(static_cast<unsigned int>(aID) <= myTimers.size() && "timerID larger than myTimers.size()");
	myTimers[aID].Resume(myTime);
}

const Time& TimerManager::MasterTotalTime() const
{
	return myMasterTimer.GetElapsedTime();
}

const Time& TimerManager::MasterFrameTime() const
{
	return myMasterTimer.GetFrameTime();
}

int TimerManager::CreateTimer()
{
	Timer newTimer;
	myTimers.push_back(newTimer);

	return myTimers.size() - 1;
}

Timer& TimerManager::GetTimer(int aID)
{
	assert(aID >= 0 && "timerID smaller than 0");
	assert(static_cast<unsigned int>(aID) <= myTimers.size() && "timerID larger than myTimers.size()");
	return myTimers[aID];
}

const LARGE_INTEGER TimerManager::GetTotalTime() const
{
	return myTime;
}

const LARGE_INTEGER TimerManager::GetFrequency() const
{
	return myClockFrequency;
}