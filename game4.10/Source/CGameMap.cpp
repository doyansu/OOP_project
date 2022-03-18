#include <stdlib.h>
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
		init();
	}

	void CGameMap::init()
	{
		this->SetXY(_X, _Y);
		for (int i = 0; i < 200; i++)
		{
			for (int j = 0; j < 200; j++)
			{
				_map[i][j] = 0;
			}
		}
	}

	void CGameMap::LoadBitmap()
	{
		_floor.LoadBitmap(IDB_FLOOR_1);
		_wall.LoadBitmap(IDB_WALL_1);
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
		for (int i = 0; i < 200; i++)
		{
			for (int j = 0; j < 200; j++)
			{
				switch (_map[i][j])
				{
					case 0:
						break;
					case 1:
						_floor.SetTopLeft(_x + (_MW * i), _y + (_MH * j));
						_floor.ShowBitmap();
						break;
					case 2:
						_wall.SetTopLeft(_x + (_MW * i), _y + (_MH * j));
						_wall.ShowBitmap();
					default:
						ASSERT(0);
				}
			}
		}
	}

	void CGameMap::GenerateMap()
	{
		init();
		//int Room[5][5];
		const int INTERNAL = 40;
		const int NROOMS = 200 / INTERNAL;

		for (int i = 0; i < NROOMS; i++)
		{
			for (int j = 0; j < NROOMS; j++)
			{
				int height = 16 + (rand() % 6), weight = 16 + (rand() % 6);
				int orgx = (INTERNAL >> 1) + INTERNAL * i - (height>>1), orgy = (INTERNAL>>1) + INTERNAL * j - (weight >> 1);
				
				for (int x = 0; x < height; x++)
				{
					for (int y = 0; y < weight; y++)
					{
						_map[orgx + x][orgy + y] = 1;
					}
				}
			}
		}
	}
}