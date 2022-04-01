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
		int AnimaSize = 3;
		_animas.reserve(AnimaSize);
		for (int i = 0; i < AnimaSize; i++)
			_animas.push_back(CAnimation());
		Reset();
	}

	void CGameMap::Reset()
	{
		_moveSpeed = 5;
		_sx = _sy = 0;
		for (int i = 0; i < 200; i++)
		{
			for (int j = 0; j < 200; j++)
			{
				_map[i][j] = MapContent::NULLPTR;
			}
		}
		_animaIterator = _animas.begin();
	}

	void CGameMap::LoadBitmap()
	{
		_animaIterator = GetAnima(MapContent::NULLPTR);
		_animaIterator->AddBitmap(IDB_FLOOR_1, RGB(255, 255, 255));
		_animaIterator = GetAnima(MapContent::FLOOR);
		_animaIterator->AddBitmap(IDB_FLOOR_1, RGB(255, 255, 255));
		_animaIterator = GetAnima(MapContent::WALL);
		_animaIterator->AddBitmap(IDB_WALL_1, RGB(255, 255, 255));
		_animaIterator = _animas.begin();
	}

	void CGameMap::OnMove(int px, int py)
	{
		//	動畫移動
		for (int i = 0; i < (int)_animas.size(); i++)
			_animas.at(i).OnMove();
			
		//	螢幕跟隨角色
		this->SetScreen(px - (SIZE_X>>1), py - (SIZE_Y>>1));
	}

	void CGameMap::OnShow()
	{
		for (int i = 0; i < 200; i++)
		{
			for (int j = 0; j < 200; j++)
			{
				int mx = _MAPW * i, my = _MAPH * j;
				if ((this->InScreen(mx, my, mx + _MAPW, my + _MAPH)) && _map[i][j] != MapContent::NULLPTR)
				{
					_animaIterator = GetAnima(_map[i][j]);
					_animaIterator->SetTopLeft(ScreenX(mx), ScreenY(my));
					_animaIterator->OnShow();
				}
			}
		}
	}

	void CGameMap::GenerateMap()
	{
		Reset();
		
		const int INTERNAL = 35;
		const int NROOMS = 4;
		int Room[NROOMS][NROOMS][2];
		bool mask[NROOMS][NROOMS];
		memset(mask, false, sizeof(mask));

		//	決定房間有無
		for (int i = 0; i < NROOMS; i++) 
		{
			int r = 1 + (rand() % (NROOMS));
			for (int j = 0; j < r; j++)
			{
				mask[i][j] = true;
			}
		}

		//	決定房間寬高、設定中心區域
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

		//	設定房間之間的通道
		for (int i = 0; i < NROOMS; i++)
		{

			for (int j = 0; j < NROOMS; j++)
			{
				if (mask[i][j] == false)
					continue;
				int h1 = Room[i][j][0], h2;
				int w1 = Room[i][j][1], w2;
				int cx = (INTERNAL >> 1) + INTERNAL * i;
				int cy = (INTERNAL >> 1) + INTERNAL * j;
				if (mask[i + 1][j] && (i + 1) != NROOMS) {
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
				if (mask[i][j + 1] && (j + 1) != NROOMS) {
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

	}

	void CGameMap::OnKeyDown(char nChar)
	{

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

	void CGameMap::SetScreen(int x, int y)
	{
		_sx = x;
		_sy = y;
	}

	vector<CAnimation>::iterator CGameMap::GetAnima(MapContent Type)
	{
		vector<CAnimation>::iterator iterator;
		switch (Type)
		{
		case game_framework::CGameMap::MapContent::NULLPTR:
			iterator = _animas.begin();
			break;
		case game_framework::CGameMap::MapContent::FLOOR:
			iterator = _animas.begin() + 1;
			break;
		case game_framework::CGameMap::MapContent::WALL:
			iterator = _animas.begin() + 2;
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