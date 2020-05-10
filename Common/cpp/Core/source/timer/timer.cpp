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

// 計測開始
void Timer::start()
{
	mIsMeasuring = true;
	QueryPerformanceCounter(&mStartTime);
}

// 計測終了
void Timer::stop()
{
	mIsMeasuring = false;
	QueryPerformanceCounter(&mStopTime);
}

// 時間取得
double Timer::getTime() const
{
	// msecの時間を計算
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
