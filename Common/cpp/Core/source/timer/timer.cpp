#include "pch.h"
#include "core/timer/timer.h"

Timer::Timer()
	: mIsMeasuring(false)
	, mFrequency()
	, mStartTime()
	, mStopTime()
{
	QueryPerformanceFrequency(&mFrequency);
	QueryPerformanceCounter(&mStartTime);
	QueryPerformanceCounter(&mStopTime);
}

Timer::~Timer()
{
}

// �v���J�n
void Timer::start()
{
	mIsMeasuring = true;
	QueryPerformanceCounter(&mStartTime);
}

// �v���I��
void Timer::stop()
{
	mIsMeasuring = false;
	QueryPerformanceCounter(&mStopTime);
}

// ���Ԏ擾
double Timer::getTime() const
{
	// msec�̎��Ԃ��v�Z
	auto CalcMsec = [](const LARGE_INTEGER& start, const LARGE_INTEGER& end, const LARGE_INTEGER& freq) -> double
	{
		return static_cast<double>(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
	};

	if (mIsMeasuring)
	{
		LARGE_INTEGER curTime;
		QueryPerformanceCounter(&curTime);
		return CalcMsec(mStartTime, curTime, mFrequency);
	}
	else
	{
		return CalcMsec(mStartTime, mStopTime, mFrequency);
	}
}
