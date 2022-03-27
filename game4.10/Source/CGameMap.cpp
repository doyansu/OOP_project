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
		:_MAPW(25), _MAPH(25)
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

	void CGameMap::OnMove(int px, int py)
	{
		//���ʿù�
		/*if (_isMovingLeft)
			_sx -= _moveSpeed;
		if (_isMovingRight)
			_sx += _moveSpeed;
		if (_isMovingUp)
			_sy -= _moveSpeed;
		if (_isMovingDown)
			_sy += _moveSpeed;*/
		//	�ù����H����
		this->SetScreen(px - (SIZE_X>>1), py - (SIZE_Y>>1));
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
		int Room[NROOMS][NROOMS][2];
		bool mask[NROOMS][NROOMS];
		memset(mask, false, sizeof(mask));

		//	�M�w�ж����L
		for (int i = 0; i < NROOMS; i++) 
		{
			int r = 1 + (rand() % (NROOMS - 1));
			r = 5;
			for (int j = 0; j < r; j++)
			{
				mask[i][j] = true;
			}
		}

		//	�M�w�ж��e���B�]�w���߰ϰ�
		for (int i = 0; i < NROOMS; i++)
		{
			for (int j = 0; j < NROOMS; j++)
			{
				if (!mask[i][j])
					continue;
				int height = 15 + (rand() % 3) * 2, weight = 15 + (rand() % 3) * 2;
				int orgx = (INTERNAL >> 1) + INTERNAL * i - (height >> 1);
				int orgy = (INTERNAL >> 1) + INTERNAL * j - (weight >> 1);
				Room[i][j][0] = height;
				Room[i][j][1] = weight;
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

		//	�]�w�ж��������q�D
		for (int i = 0; i < NROOMS - 1; i++)
		{

			for (int j = 0; j < NROOMS - 1; j++)
			{
				int h1 = Room[i][j][0], h2;
				int w1 = Room[i][j][1], w2;
				int cx = (INTERNAL >> 1) + INTERNAL * i;
				int cy = (INTERNAL >> 1) + INTERNAL * j;
				if (mask[i + 1][j]) {
					h2 = Room[i + 1][j][0];
					w2 = Room[i + 1][j][1];
					for (int x = cx + h1 / 2 + 1 ; x < cx + INTERNAL - h2 / 2; x++)
					{
						_map[x][cy + 3] = MapContent::WALL;
						_map[x][cy - 3] = MapContent::WALL;
						for (int y = -2; y < 3; y++)
						{
							_map[x][cy + y] = MapContent::FLOOR;
						}
					}
				}
				if (mask[i][j + 1]) {
					h2 = Room[i][j + 1][0];
					w2 = Room[i][j + 1][1];
					for (int y = cy + w1 / 2 + 1; y < cy + INTERNAL - w2 / 2; y++)
					{
						_map[cx + 3][y] = MapContent::WALL;
						_map[cx - 3][y] = MapContent::WALL;
						for (int x = -2; x < 3; x++)
						{
							_map[cx + x][y] = MapContent::FLOOR;
						}
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

	bool CGameMap::IsEmpty(int x, int y)
	{
		x /= _MAPW;
		y /= _MAPH;
		return _map[x][y] == MapContent::FLOOR;
	}

	bool CGameMap::InScreen(int x, int y, int mw, int mh)
	{
		int x1 = _sx;
		int y1 = _sy;
		int x2 = x1 + SIZE_X;
		int y2 = y1 + SIZE_Y;
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