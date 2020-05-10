#pragma once

#include "core/windows/myWindows.h"

//! @brief タイマー
class Timer
{
public:
	Timer();
	~Timer();

	//! @brief 計測開始
	void start();

	//! @brif 計測終了
	void stop();

	//! @brief 時間取得
	double getTime() const;

private:
	bool mIsMeasuring; //!< 計測中か

	LARGE_INTEGER mFrequency; //!< 周波数
	LARGE_INTEGER mStartTime; //!< 開始時間
	LARGE_INTEGER mStopTime; //!< 終了時間
};