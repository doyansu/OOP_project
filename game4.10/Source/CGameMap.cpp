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
		:_MW(25), _MH(25)
	{
		init();
	}

	void CGameMap::init()
	{
		_moveSpeed = 5;
		_sx = _sy = 0;
		_isMovingLeft = _isMovingRight = _isMovingUp = _isMovingDown = false;
		memset(_map, 0, sizeof(_map));
	}

	void CGameMap::LoadBitmap()
	{
		_floor.LoadBitmap(IDB_FLOOR_1);
		_wall.LoadBitmap(IDB_WALL_1);
	}

	void CGameMap::OnMove()
	{
		if (_isMovingLeft)
			_sx -= _moveSpeed;
		if (_isMovingRight)
			_sx += _moveSpeed;
		if (_isMovingUp)
			_sy -= _moveSpeed;
		if (_isMovingDown)
			_sy += _moveSpeed;
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
						_floor.SetTopLeft(ScreenX(_MW * i), ScreenY(_MH * j));
						_floor.ShowBitmap();
						break;
					case 2:
						_wall.SetTopLeft(ScreenX(_MW * i), ScreenY(_MH * j));
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

	void CGameMap::OnKeyUp(char nChar)
	{
		const char KEY_LEFT = 0x25; 
		const char KEY_UP = 0x26;
		const char KEY_RIGHT = 0x27; 
		const char KEY_DOWN = 0x28; 
		if (nChar == KEY_LEFT)
			this->SetMovingLeft(false);
		if (nChar == KEY_RIGHT)
			this->SetMovingRight(false);
		if (nChar == KEY_UP)
			this->SetMovingUp(false);
		if (nChar == KEY_DOWN)
			this->SetMovingDown(false);
	}

	void CGameMap::OnKeyDown(char nChar)
	{
		const char KEY_LEFT = 0x25; 
		const char KEY_UP = 0x26; 
		const char KEY_RIGHT = 0x27; 
		const char KEY_DOWN = 0x28; 
		if (nChar == KEY_LEFT)
			this->SetMovingLeft(true);
		if (nChar == KEY_RIGHT)
			this->SetMovingRight(true);
		if (nChar == KEY_UP)
			this->SetMovingUp(true);
		if (nChar == KEY_DOWN)
			this->SetMovingDown(true);
	}

	int CGameMap::ScreenX(int x)
	{
		return x - _sx;
	}

	int CGameMap::ScreenY(int y)
	{
		return y - _sy;
	}

	void CGameMap::SetMovingDown(bool flag)
	{
		_isMovingDown = flag;
	}

	void CGameMap::SetMovingLeft(bool flag)
	{
		_isMovingLeft = flag;
	}

	void CGameMap::SetMovingRight(bool flag)
	{
		_isMovingRight = flag;
	}

	void CGameMap::SetMovingUp(bool flag)
	{
		_isMovingUp = flag;
	}


}