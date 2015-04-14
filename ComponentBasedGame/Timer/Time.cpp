#include "Time.h"


Time::Time()
{
	myRawTime = 0;
}


Time::~Time()
{
}

void Time::Update(double aRawTime)
{
	myRawTime = aRawTime;
}