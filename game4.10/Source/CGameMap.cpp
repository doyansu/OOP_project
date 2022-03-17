#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameMap.h"

namespace game_framework {
	CGameMap::CGameMap()
		:_X(20), _Y(40), _MW(120), _MH(100)
	{
		int map_init[5][5] = { 
		{1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1}, 
		{1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1}
		};
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				_map[i][j] = map_init[i][j];
			}
		}
	}

	void CGameMap::LoadBitmap()
	{
		_floor.LoadBitmap(IDB_GATE1);
	}

	void CGameMap::OnShow()
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				switch (_map[i][j])
				{
					case 1:
						_floor.SetTopLeft(_X + (_MW * i), _Y + (_MH * j));
						_floor.ShowBitmap();
						break;
					default:
						ASSERT(0);
				}
			}
		}
	}
}