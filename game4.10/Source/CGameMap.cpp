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
		:_MAPW(25), _MAPH(25), _SCREENW(SIZE_X), _SCREENH(SIZE_Y)
	{
		init();
	}

	void CGameMap::init()
	{
		_moveSpeed = 5;
		_sx = _sy = 0;
		_isMovingLeft = _isMovingRight = _isMovingUp = _isMovingDown = false;
		CMovingBitmap add_bmp;
		for (int i = 0; i < 3; i++)
		{
			_bmp.push_back(add_bmp);
		}
		
		for (int i = 0; i < 200; i++)
		{
			for (int j = 0; j < 200; j++)
			{
				_map[i][j] = MapContent::NENO;
			}
		}

		_bmpIterator = _bmp.begin();
	}

	void CGameMap::Reset()
	{
		this->init();
	}

	void CGameMap::LoadBitmap()
	{
		_bmpIterator = GetBmp(MapContent::FLOOR);
		_bmpIterator->LoadBitmap(IDB_FLOOR_1);
		_bmpIterator = GetBmp(MapContent::WALL);
		_bmpIterator->LoadBitmap(IDB_WALL_1);
	}

	void CGameMap::OnMove()
	{
		//²¾°Ê¿Ã¹õ
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
				int mx = _MAPW * i, my = _MAPH * j;
				if ((this->InScreen(mx, my, mx + _MAPW, my + _MAPH)) && _map[i][j] != MapContent::NENO)
				{
					_bmpIterator = GetBmp(_map[i][j]);
					_bmpIterator->SetTopLeft(ScreenX(mx), ScreenY(my));
					_bmpIterator->ShowBitmap();
				}
			}
		}
	}

	void CGameMap::GenerateMap()
	{
		init();
		
		const int INTERNAL = 40;
		const int NROOMS = 200 / INTERNAL;
		int Room[NROOMS][NROOMS][4];
		bool mask[NROOMS][NROOMS];
		memset(mask, false, sizeof(mask));

		for (int i = 0; i < NROOMS; i++) 
		{
			int r = 1 + (rand() % (NROOMS - 1));
			r = 5;
			for (int j = 0; j < r; j++)
			{
				mask[i][j] = true;
			}
		}

		for (int i = 0; i < NROOMS; i++)
		{
			for (int j = 0; j < NROOMS; j++)
			{
				if (!mask[i][j])
					continue;
				int height = 16 + (rand() % 6), weight = 16 + (rand() % 6);
				int orgx = (INTERNAL >> 1) + INTERNAL * i - (height >> 1), orgy = (INTERNAL >> 1) + INTERNAL * j - (weight >> 1);
				Room[i][j][0] = (INTERNAL >> 1) + INTERNAL * i;
				Room[i][j][1] = (INTERNAL >> 1) + INTERNAL * j;
				Room[i][j][2] = height;
				Room[i][j][3] = weight;
				for (int x = 0; x < height; x++)
				{
					for (int y = 0; y < weight; y++)
					{
						_map[orgx + x][orgy + y] = MapContent::FLOOR;
					}
				}

				for (int x = 0; x < height; x++)
				{
					_map[orgx + x][orgy - 1] = MapContent::WALL;
					_map[orgx + x][orgy + weight] = MapContent::WALL;
				}

				for (int y = -1; y < weight + 1; y++)
				{
					_map[orgx - 1][orgy + y] = MapContent::WALL;
					_map[orgx + height][orgy + y] = MapContent::WALL;
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

	bool CGameMap::isEmpty(int x, int y)
	{
		x /= _MAPW;
		y /= _MAPH;
		return _map[x][y] == MapContent::FLOOR;
	}

	bool CGameMap::InScreen(int x, int y, int mw, int mh)
	{
		int x1 = _sx;
		int y1 = _sy;
		int x2 = x1 + _SCREENW;
		int y2 = y1 + _SCREENH;
		return (mw >= x1 && x <= x2 && mh >= y1 && y <= y2);
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

	void CGameMap::SetScreen(int x, int y)
	{
		_sx = x;
		_sy = y;
	}

	vector<CMovingBitmap>::iterator CGameMap::GetBmp(MapContent bmpType)
	{
		vector<CMovingBitmap>::iterator iterator;
		switch (bmpType)
		{
		case game_framework::CGameMap::MapContent::NENO:
			iterator = _bmp.begin();
			break;
		case game_framework::CGameMap::MapContent::FLOOR:
			iterator = _bmp.begin() + 1;
			break;
		case game_framework::CGameMap::MapContent::WALL:
			iterator = _bmp.begin() + 2;
			break;
		default:
			ASSERT(0);
		}
		return iterator;
	}

	int CGameMap::GetScreenX()
	{
		return _sx;
	}

	int CGameMap::GetScreenY()
	{
		return _sy;
	}

	

}