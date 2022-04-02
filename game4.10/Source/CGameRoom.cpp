#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameRoom.h"

namespace game_framework 
{
	CGameRoom::CGameRoom()
	{
		_centerX = 0;
		_centerY = 0;
		_width = _high = 1;
	}

	int CGameRoom::CenterX()
	{
		return _centerX;
	}

	int CGameRoom::CenterY()
	{
		return _centerY;
	}

	int CGameRoom::Width()
	{
		return _width;
	}

	int CGameRoom::High()
	{
		return _high;
	}
}
