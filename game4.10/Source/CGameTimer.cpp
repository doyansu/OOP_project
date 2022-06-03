#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameTimer.h"

namespace game_framework
{
	int CGameTimer::_currentTime = 0;

	CGameTimer::CGameTimer()
	{
		_startPoint = _currentTime;
	}

	CGameTimer& CGameTimer::Instance()
	{
		static CGameTimer timer;
		return timer;
	}

	int CGameTimer::CurrentTime()
	{
		return _currentTime;
	}

	void CGameTimer::Timing()
	{
		_currentTime++;
	}

	void CGameTimer::SetStartPoint(int value)
	{
		if (value < 0 || value > _currentTime)
			_startPoint = _currentTime;
		else
			_startPoint = value;
	}

	int CGameTimer::GetStartPoint()
	{
		return _startPoint;
	}

	int CGameTimer::GetTimingTime()
	{
		return _currentTime - _startPoint;
	}

	int CGameTimer::ConvertToSeconds(int time)
	{
		return time / GAME_ONE_SECONED;	
	}

}