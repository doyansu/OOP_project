#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameMap.h"

namespace game_framework {
	CGameMap::CGameMap()
		:_X(0), _Y(0), _MW(25), _MH(25)
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
		_floor.LoadBitmap(IDB_FLOOR_1);
	}

	void CGameMap::OnMove()
	{
		if (_isMovingLeft)
			_x += _moveSpeed;
		if (_isMovingRight)
			_x -= _moveSpeed;
		if (_isMovingUp)
			_y += _moveSpeed;
		if (_isMovingDown)
			_y -= _moveSpeed;
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
						_floor.SetTopLeft(_x + (_MW * i), _y + (_MH * j));
						_floor.ShowBitmap();
						break;
					default:
						ASSERT(0);
				}
			}
		}
	}
}