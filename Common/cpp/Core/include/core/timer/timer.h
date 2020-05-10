#pragma once

#include "core/windows/myWindows.h"

//! @brief �^�C�}�[
class Timer
{
public:
	Timer();
	~Timer();

	//! @brief �v���J�n
	void start();

	//! @brif �v���I��
	void stop();

	//! @brief ���Ԏ擾
	double getTime() const;

private:
	bool mIsMeasuring; //!< �v������

	LARGE_INTEGER mFrequency; //!< ���g��
	LARGE_INTEGER mStartTime; //!< �J�n����
	LARGE_INTEGER mStopTime; //!< �I������
};