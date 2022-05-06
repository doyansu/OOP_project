#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CUIMinMap.h"

namespace game_framework
{
	CUIMinMap::CUIMinMap()
	{
		_sx = _sy = 0;
	}

	CUIMinMap::SetXY(int x, int y)
	{
		_sx = x;
		_sy = y;
	}
}