#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameMap.h"


namespace game_framework {
	CGameMap::CGameMap()
		:_MAPW(MYMAPWIDTH), _MAPH(MYMAPHIGH), _MAXNOFROOM(MYMAXNOFROOM)
	{
		// 動畫載入
		const int AnimaSize = 4;
		_animas.reserve(AnimaSize);
		for (int i = 0; i < AnimaSize; i++)
			_animas.push_back(CAnimation());

		_Rooms = nullptr;

		Reset();
	}

	CGameMap::~CGameMap()
	{
		free();
	}

	void CGameMap::Reset()
	{
		_sx = _sy = 0;
		for (int i = 0; i < 200; i++)
		{
			for (int j = 0; j < 200; j++)
			{
				_map[i][j] = MapContent::NULLPTR;
			}
		}
		_animaIterator = _animas.begin();

		free();
		_Rooms = new RoomData*[_MAXNOFROOM];
		for (int i = 0; i < _MAXNOFROOM; i++)
			_Rooms[i] = new RoomData[_MAXNOFROOM];
	}

	void CGameMap::free()
	{
		if (_Rooms != nullptr)
		{
			for (int i = 0; i < _MAXNOFROOM; i++)
					delete[] _Rooms[i];
			delete[] _Rooms;
			_Rooms = nullptr;
		}
	}

	void CGameMap::LoadBitmap()
	{
		_animaIterator = GetAnima(MapContent::NULLPTR);
		_animaIterator->AddBitmap(IDB_FLOOR_1, RGB(255, 255, 255));
		_animaIterator = GetAnima(MapContent::FLOOR);
		_animaIterator->AddBitmap(IDB_FLOOR_1, RGB(255, 255, 255));
		_animaIterator = GetAnima(MapContent::WALL);
		_animaIterator->AddBitmap(IDB_WALL_1, RGB(255, 255, 255));
		_animaIterator = GetAnima(MapContent::AISLEWALL);
		_animaIterator->AddBitmap(IDB_Wall0, RGB(255, 255, 255));
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
		
		const int INTERNAL = ROOMINTERNAL;
		const int NROOMS = _MAXNOFROOM;
		/*int Room[NROOMS][NROOMS][2];
		bool mask[NROOMS][NROOMS];
		memset(mask, false, sizeof(mask));*/

		//	決定房間有無、類型
		int rx = 2 + (rand() % (NROOMS - 1));
		int ry;
		for (int i = 0; i < rx; i++)
		{
			ry = 2 + (rand() % (NROOMS - 1));
			for (int j = 0; j < ry; j++)
			{
				_Rooms[i][j]._hasRoom = true;
				_Rooms[i][j]._roomType = RoomData::RoomType::NORMAL;
			}
		}
		_Rooms[0][0]._roomType = RoomData::RoomType::INIT;
		_Rooms[rx - 1][ry - 1]._roomType = RoomData::RoomType::END;

		//	決定房間寬高、設定中心區域
		for (int i = 0; i < NROOMS; i++)
		{
			for (int j = 0; j < NROOMS; j++)
			{
				if (!_Rooms[i][j]._hasRoom)
					continue;
				int height = 15 + (rand() % 5) * 2, weight = 15 + (rand() % 5) * 2;// 打成身高體重QQ 應該是寬高
				int orgx = (INTERNAL >> 1) + INTERNAL * i - (height >> 1);
				int orgy = (INTERNAL >> 1) + INTERNAL * j - (weight >> 1);
				// 初始化房間參數
				_Rooms[i][j]._width = height; 
				_Rooms[i][j]._high = weight;
				_Rooms[i][j]._centerX = (INTERNAL >> 1) + INTERNAL * i;
				_Rooms[i][j]._centerY = (INTERNAL >> 1) + INTERNAL * j;
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
				if (_Rooms[i][j]._hasRoom == false)
					continue;
				int h1 = _Rooms[i][j]._width, h2; // 寬高好像用反了
				int w1 = _Rooms[i][j]._high, w2;
				int cx = _Rooms[i][j]._centerX;
				int cy = _Rooms[i][j]._centerY;
				if ((i + 1) != NROOMS && _Rooms[i + 1][j]._hasRoom) {
					_Rooms[i][j]._hasRoad[3] = true;
					_Rooms[i + 1][j]._hasRoad[2] = true;
					h2 = _Rooms[i + 1][j]._width;
					w2 = _Rooms[i + 1][j]._high;
					// 主通道
					for (int x = cx + h1 / 2 + 1 ; x < cx + INTERNAL - h2 / 2; x++)
					{
						_map[x][cy + 3] = MapContent::WALL;
						_map[x][cy - 3] = MapContent::WALL;
						for (int y = -2; y < 3; y++)
						{
							_map[x][cy + y] = MapContent::FLOOR;
						}
					}
					// 進房間區隔
					for (int y = -2; y < 3; y++) {
						_map[cx + h1 / 2 + 1][cy + y] = MapContent::AISLEWALL;
						_map[cx + INTERNAL - h2 / 2 - 1][cy + y] = MapContent::AISLEWALL;
					}
				}
				if ((j + 1) != NROOMS && _Rooms[i][j + 1]._hasRoom) {
					_Rooms[i][j]._hasRoad[1] = true;
					_Rooms[i][j + 1]._hasRoad[0] = true;
					h2 = _Rooms[i][j + 1]._width;
					w2 = _Rooms[i][j + 1]._high;
					for (int y = cy + w1 / 2 + 1; y < cy + INTERNAL - w2 / 2; y++)
					{
						_map[cx + 3][y] = MapContent::WALL;
						_map[cx - 3][y] = MapContent::WALL;
						for (int x = -2; x < 3; x++)
						{
							_map[cx + x][y] = MapContent::FLOOR;
						}
					}
					for (int x = -2; x < 3; x++)
					{
						_map[cx + x][cy + w1 / 2 + 1] = MapContent::AISLEWALL;
						_map[cx + x][cy + INTERNAL - w2 / 2 - 1] = MapContent::AISLEWALL;
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

	bool CGameMap::IsContent(int x, int y, CGameMap::MapContent content)
	{
		x /= _MAPW;
		y /= _MAPH;
		return _map[x][y] == content;
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
		case game_framework::CGameMap::MapContent::AISLEWALL:
			iterator = _animas.begin() + 3;
			break;
		default:
			ASSERT(0);
		}
		return iterator;
	}

	RoomData CGameMap::GetRoom(int i, int j)
	{
		if(i < 0 && i >= _MAXNOFROOM && j < 0 && j >= _MAXNOFROOM)
			ASSERT(0);
		return _Rooms[i][j];
	}

	int CGameMap::GetScreenX()
	{
		return _sx;
	}

	int CGameMap::GetScreenY()
	{
		return _sy;
	}


	// RoomData class
	RoomData::RoomData()
	{
		_centerX = 0;
		_centerY = 0;
		_width = _high = 1;
		_hasRoad[0] = _hasRoad[1] = _hasRoad[2] = _hasRoad[3] = false;
		_hasRoom = false;
	}

	int RoomData::CenterX()
	{
		return _centerX;
	}

	int RoomData::CenterY()
	{
		return _centerY;
	}

	int RoomData::Width()
	{
		return _width;
	}

	int RoomData::High()
	{
		return _high;
	}

	bool RoomData::HasRoad(int index)
	{
		if (index < 0 || index > 3)
			ASSERT(0);	
		return _hasRoad[index];
	}

	RoomData::RoomType RoomData::GetRoomType()
	{
		return _roomType;
	}

}