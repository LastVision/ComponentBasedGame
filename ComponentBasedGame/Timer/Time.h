#pragma once
class Time
{
public:
	Time();
	~Time();

	void Update(double aRawTime);

	float GetHours() const;
	float GetMinutes() const;
	float GetSeconds() const;
	double GetMiliSeconds() const;
	unsigned long long GetMicroSeconds() const;

private:
	double myRawTime;
};

inline float Time::GetHours() const
{
	return GetMinutes() / 60.f;
}

inline float Time::GetMinutes() const
{
	return GetSeconds() / 60.f;
}

inline float Time::GetSeconds() const
{
	return static_cast<float>(myRawTime);
}

inline double Time::GetMiliSeconds() const
{
	return GetSeconds() * 1000;
}

inline unsigned long long Time::GetMicroSeconds() const
{
	return static_cast<long long>(GetMiliSeconds()) * 1000;
}