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
		const int AnimaSize = 5;
		_animas.reserve(AnimaSize);
		for (int i = 0; i < AnimaSize; i++)
			_animas.push_back(vector<CAnimation>());

		_Rooms = nullptr; 
		_roomTree = nullptr;

		Reset();
	}

	CGameMap::~CGameMap()
	{
		free();
	}

	void CGameMap::Reset()
	{
		_sx = _sy = 0;
		for (int i = 0; i < MYMAPSIZE; i++)
		{
			for (int j = 0; j < MYMAPSIZE; j++)
			{
				_map[i][j] = MapContent();
			}
		}

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
		if (_roomTree != nullptr)
		{
			_roomTree->freeTree();
			_roomTree = nullptr;
		}
		
	}

	void CGameMap::LoadBitmap()
	{
		vector<vector<CAnimation>>::iterator animas = _animas.begin();
		vector<CAnimation>::iterator p;

		// NULLPTR		1
		//*animas = vector<CAnimation>(1);
		animas->push_back(CAnimation());
		p = animas++->begin();
		p++->AddBitmap(IDB_FLOOR_1, RGB(255, 255, 255));

		// FLOOR		6
		animas->reserve(6);
		for(int i = 0; i < 6; i++)
			animas->push_back(CAnimation());
		p = animas++->begin();
		p++->AddBitmap(IDB_Floor_0_0, RGB(255, 255, 255));
		p++->AddBitmap(IDB_floor_0_1, RGB(255, 255, 255));
		p++->AddBitmap(IDB_Floor_0_2, RGB(255, 255, 255));
		p++->AddBitmap(IDB_Floor_0_3, RGB(255, 255, 255));
		p++->AddBitmap(IDB_Floor_0_4, RGB(255, 255, 255));
		p++->AddBitmap(IDB_Floor_0_5, RGB(255, 255, 255));
		

		// WALL			2
		animas->reserve(2);
		for (int i = 0; i < 2; i++)
			animas->push_back(CAnimation());
		p = animas++->begin();
		p++->AddBitmap(IDB_Wall_0_0, RGB(255, 255, 255));
		p++->AddBitmap(IDB_Wall_0_1, RGB(255, 255, 255));

		// AISLEWALL	1
		animas->push_back(CAnimation());
		p = animas++->begin();
		p++->AddBitmap(IDB_AISLEWALL_0, RGB(255, 255, 255));

		// WALLBOTTOM	1
		animas->push_back(CAnimation());
		p = animas++->begin();
		p++->AddBitmap(IDB_Wall_0_WallBottom, RGB(255, 255, 255));

	}

	void CGameMap::OnMove(int px, int py)
	{
		//	動畫移動
		for (int i = 0; i < (int)_animas.size(); i++)
			for(int j = 0; j < (int)_animas.at(i).size(); j++)
				_animas.at(i).at(j).OnMove();
			
		//	螢幕跟隨角色
		this->SetScreen(px - (SIZE_X>>1), py - (SIZE_Y>>1));
	}

	void CGameMap::OnShow(bool cover)
	{
		for (int i = 0; i < MYMAPSIZE; i++)
		{
			for (int j = 0; j < MYMAPSIZE; j++)
			{
				int mx = _MAPW * i, my = _MAPH * j;
				MapContent content = _map[i][j];
				if (!content.IsType(ContentType::NULLPTR) && (this->InScreen(mx, my, mx + _MAPW, my + _MAPH)))
				{
					vector<CAnimation>::iterator p = content.GetAnima();

					if (cover)
					{
						if (content.IsCover() && content.IsType(ContentType::WALL))
						{
							p->SetTopLeft(ScreenX(mx), ScreenY(my - 12));
							p->OnShow();
							if (content.IsShow())
							{
								p = GetAnima(ContentType::WALLBOTTOM, 0);
								p->SetTopLeft(ScreenX(mx), ScreenY(my + 13));
								p->OnShow();
							}
						}
					}
					else 
					{
						if (content.IsType(ContentType::WALL))
						{
							p->SetTopLeft(ScreenX(mx), ScreenY(my - 12));
							p->OnShow();
							p = GetAnima(ContentType::WALLBOTTOM, 0);
							p->SetTopLeft(ScreenX(mx), ScreenY(my + 13));
							p->OnShow();
						}
						else
						{
							p->SetTopLeft(ScreenX(mx), ScreenY(my));
							p->OnShow();
						}
					}
				}
			}
		}
	}

	void CGameMap::GenerateMap(bool hasBOSS)
	{
		Reset();
		
		const int INTERNAL = ROOMINTERNAL;
		const int NROOMS = _MAXNOFROOM;

		// 初始房間參數
		_Rooms[MYORGROOM][MYORGROOM]._hasRoom = true;
		_Rooms[MYORGROOM][MYORGROOM]._roomType = RoomData::RoomType::INIT;
		_Rooms[MYORGROOM][MYORGROOM]._width = 17;
		_Rooms[MYORGROOM][MYORGROOM]._high = 17;
		_Rooms[MYORGROOM][MYORGROOM]._centerX = (INTERNAL >> 1) + INTERNAL * MYORGROOM;
		_Rooms[MYORGROOM][MYORGROOM]._centerY = (INTERNAL >> 1) + INTERNAL * MYORGROOM;

		_roomTree = new Point(MYORGROOM, MYORGROOM);
		
		
		// 隨機選一個方向開始增加房間
		queue<CGameMap::Point*> queue;
		CGameMap::Point* start = new Point(MYORGROOM, MYORGROOM);
		start->Set((rand() % 2), MYORGROOM + (1 ^ ((1 ^ -1) * (rand() % 2))));
		queue.push(start);
		_roomTree->AddChild(start);
		start->SetParent(_roomTree);
		_Rooms[start->Get(0)][start->Get(1)]._roomType = RoomData::RoomType::NORMAL;

		int specialRoom = 1 + (rand() % 3);						// 特殊房間數
		int normalRoom = 1 + (rand() % 3);						// 一般房間數
		int dir[4][2] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };	// 搜索用向量
		while (!queue.empty())
		{
			CGameMap::Point* point = queue.front();
			int x = point->Get(0), y = point->Get(1);

			// 初始化房間參數
			_Rooms[x][y]._hasRoom = true;
			_Rooms[x][y]._centerX = (INTERNAL >> 1) + INTERNAL * x;
			_Rooms[x][y]._centerY = (INTERNAL >> 1) + INTERNAL * y;

			// 根據類型變化
			switch (_Rooms[x][y]._roomType)
			{
			case RoomData::RoomType::NORMAL:
			{
				_Rooms[x][y]._width = 15 + (rand() % 5) * 2;
				_Rooms[x][y]._high = 15 + (rand() % 5) * 2;
				
				//	插入特殊房間
				if (specialRoom > 0)
				{
					int nx, ny, m = 10;
					do {
						int r = rand() % 4;
						nx = x + dir[r][0], ny = y + dir[r][1];
					} while ((nx < 0 || ny < 0 || nx == MYMAXNOFROOM || ny == MYMAXNOFROOM || _Rooms[nx][ny]._hasRoom) && m-- > 0);

					if (nx >= 0 && ny >= 0 && nx < MYMAXNOFROOM && ny < MYMAXNOFROOM && m)
					{
						_Rooms[nx][ny]._roomType = RoomData::RoomType::TREASURE;
						_Rooms[nx][ny]._hasRoom = true;
						Point* newPoint = new CGameMap::Point(nx, ny);
						point->AddChild(newPoint);
						newPoint->SetParent(point);
						queue.push(newPoint);
						specialRoom--;
					}
				}

				//	找下一個房間
				
				int nx, ny, m = 20;
				do {
					int r = rand() % 4;
					nx = x + dir[r][0];
					ny = y + dir[r][1];
				} while ((nx < 0 || ny < 0 || nx == MYMAXNOFROOM || ny == MYMAXNOFROOM || _Rooms[nx][ny]._hasRoom) && m-- > 0);
				
				if (nx >= 0 && ny >= 0 && nx < MYMAXNOFROOM && ny < MYMAXNOFROOM && m)
				{
					if (normalRoom > 0)
					{
						_Rooms[nx][ny]._roomType = RoomData::RoomType::NORMAL;
					}
					else if(hasBOSS)
					{
						_Rooms[nx][ny]._roomType = RoomData::RoomType::BOSS;
					}
					else
					{
						_Rooms[nx][ny]._roomType = RoomData::RoomType::END;
					}
					Point* newPoint = new CGameMap::Point(nx, ny);
					point->AddChild(newPoint);
					newPoint->SetParent(point);
					queue.push(newPoint);
					normalRoom--;
				}
				else
				{
					queue.push(point->GetParent());
				}

				

				break;
			}
			case RoomData::RoomType::BOSS:
			{
				_Rooms[x][y]._width = 25;
				_Rooms[x][y]._high = 25;

				int nx, ny, m = 10;
				do {
					int r = rand() % 4;
					nx = x + dir[r][0], ny = y + dir[r][1];
				} while ((nx < 0 || ny < 0 || nx == MYMAXNOFROOM || ny == MYMAXNOFROOM || _Rooms[nx][ny]._hasRoom) && m-- > 0);

				if (nx >= 0 && ny >= 0 && nx < MYMAXNOFROOM && ny < MYMAXNOFROOM && m)
				{
					_Rooms[nx][ny]._roomType = RoomData::RoomType::END;
					Point* newPoint = new CGameMap::Point(nx, ny);
					point->AddChild(newPoint);
					newPoint->SetParent(point);
					queue.push(newPoint);
				}
				break;
			}
			case RoomData::RoomType::TREASURE:
			case RoomData::RoomType::END:
				_Rooms[x][y]._width = 11;
				_Rooms[x][y]._high = 11;
				break;
			default:
				break;
			}	
			queue.pop();
		}

		// 沒生成完成重新生成一次
		if (normalRoom > 0)
		{
			CGameMap::GenerateMap(hasBOSS);
			return;
		}
		

		/*
		// 舊版生成
		queue<CGameMap::Point> queue;
		CGameMap::Point start(MYORGROOM, MYORGROOM);
		start.Set((rand() % 2), MYORGROOM + (1 ^ ((1 ^ -1) * (rand() % 2))));
		queue.push(start);
		int specialRoom = 1 + (rand() % 3);						// 特殊房間數
		int nrmalRoom = 3 + (rand() % 3);						// 一般房間數
		int maxRoom = specialRoom + nrmalRoom + 1;				// 最大額外房間數
		int dir[4][2] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };	// 搜索用向量
		while (!queue.empty() && maxRoom)
		{
			CGameMap::Point point = queue.front();
			int x = point.Get(0), y = point.Get(1);
			if (!_Rooms[x][y]._hasRoom)
			{
				// 初始化房間參數
				_Rooms[x][y]._hasRoom = true;
				_Rooms[x][y]._roomType = RoomData::RoomType::NORMAL;
				_Rooms[x][y]._width = 15 + (rand() % 5) * 2;
				_Rooms[x][y]._high = 15 + (rand() % 5) * 2;
				_Rooms[x][y]._centerX = (INTERNAL >> 1) + INTERNAL * x;
				_Rooms[x][y]._centerY = (INTERNAL >> 1) + INTERNAL * y;

				// 隨機選周邊房間
				int rTimes = 2 + (rand() % 2);
				while (rTimes--)
				{
					int nx, ny, m = 10;
					int jx = 0, jy = 0;		// 判斷初始房間周圍不出現房間
					do {
						int r = rand() % 4;
						nx = x + dir[r][0], ny = y + dir[r][1];
						jx = abs(nx - MYORGROOM);
						jy = abs(ny - MYORGROOM);
					} while ((nx < 0 || ny < 0 || nx == MYMAXNOFROOM || ny == MYMAXNOFROOM || _Rooms[nx][ny]._hasRoom || jx + jy <= 1) && m-- > 0);
					if(nx >= 0 && ny >= 0 && nx < MYMAXNOFROOM && ny < MYMAXNOFROOM && jx + jy > 1 && m)
						queue.push(CGameMap::Point(nx, ny));
				}

				// 設定特殊房間
				if (--maxRoom == 0)// 最後一個為傳送房間
				{
					_Rooms[x][y]._roomType = RoomData::RoomType::END;
					_Rooms[x][y]._width = 11;
					_Rooms[x][y]._high = 11;
				}
				else if (maxRoom <= specialRoom)// 特殊房間
				{
					// 寶箱房間
					_Rooms[x][y]._roomType = RoomData::RoomType::TREASURE;
					_Rooms[x][y]._width = 11;
					_Rooms[x][y]._high = 11;
				}
			}
			queue.pop();
		}

		// 沒生成完成重新生成一次
		if (maxRoom)
		{
			CGameMap::GenerateMap(hasBOSS);
			return;
		}*/
		


		//	設定中心區域
		for (int i = 0; i < NROOMS; i++)
		{
			for (int j = 0; j < NROOMS; j++)
			{
				if (!_Rooms[i][j]._hasRoom)
					continue;
				int width = _Rooms[i][j]._width, high = _Rooms[i][j]._high;
				int orgx = (INTERNAL >> 1) + INTERNAL * i - (width >> 1);
				int orgy = (INTERNAL >> 1) + INTERNAL * j - (high >> 1);
				for (int x = 0; x < width; x++)
				{
					for (int y = 0; y < high; y++)
					{
						_map[orgx + x][orgy + y] = MapContent(ContentType::FLOOR, GetAnima(ContentType::FLOOR));
					}
				}

				for (int x = 0; x < width; x++)
				{
					_map[orgx + x][orgy - 1] = MapContent(ContentType::WALL, GetAnima(ContentType::WALL));
					_map[orgx + x][orgy + high] = MapContent(ContentType::WALL, GetAnima(ContentType::WALL), true);
				}

				for (int y = -1; y < high + 1; y++)
				{
					if (y < (high >> 1))
					{
						_map[orgx - 1][orgy + y] = MapContent(ContentType::WALL, GetAnima(ContentType::WALL));
						_map[orgx + width][orgy + y] = MapContent(ContentType::WALL, GetAnima(ContentType::WALL));
					}
					else
					{
						_map[orgx - 1][orgy + y] = MapContent(ContentType::WALL, GetAnima(ContentType::WALL), true);
						_map[orgx + width][orgy + y] = MapContent(ContentType::WALL, GetAnima(ContentType::WALL), true);
					}
				}

				// 一般怪物房間障礙設定
				if (_Rooms[i][j]._roomType == RoomData::RoomType::NORMAL)
				{
					normalRoomGenerate(i, j);
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

				// 左右通道
				if ((i + 1) != NROOMS && _Rooms[i + 1][j]._hasRoom) {
					_Rooms[i][j]._hasRoad[3] = true;
					_Rooms[i + 1][j]._hasRoad[2] = true;
					h2 = _Rooms[i + 1][j]._width;
					w2 = _Rooms[i + 1][j]._high;
					// 主通道
					for (int x = cx + h1 / 2 + 1 ; x < cx + INTERNAL - h2 / 2; x++)
					{
						_map[x][cy - 3] = MapContent(ContentType::WALL, GetAnima(ContentType::WALL));
						_map[x][cy + 3] = MapContent(ContentType::WALL, GetAnima(ContentType::WALL), true);
						
						for (int y = -2; y < 3; y++)
						{
							_map[x][cy + y] = MapContent(ContentType::FLOOR, GetAnima(ContentType::FLOOR));
						}
					}
					// 進房間區隔
					for (int y = -2; y < 3; y++) {
						_map[cx + h1 / 2 + 1][cy + y] = MapContent(ContentType::AISLEWALL, GetAnima(ContentType::AISLEWALL));
						_map[cx + INTERNAL - h2 / 2 - 1][cy + y] = MapContent(ContentType::AISLEWALL, GetAnima(ContentType::AISLEWALL));
					}
				}

				// 上下通道
				if ((j + 1) != NROOMS && _Rooms[i][j + 1]._hasRoom) {
					_Rooms[i][j]._hasRoad[1] = true;
					_Rooms[i][j + 1]._hasRoad[0] = true;
					h2 = _Rooms[i][j + 1]._width;
					w2 = _Rooms[i][j + 1]._high;
					for (int y = cy + w1 / 2 + 1; y < cy + INTERNAL - w2 / 2; y++)
					{
						if (y == cy + w1 / 2 + 1)
						{
							_map[cx + 3][y] = MapContent(ContentType::WALL, GetAnima(ContentType::WALL), true);
							_map[cx - 3][y] = MapContent(ContentType::WALL, GetAnima(ContentType::WALL), true);
						}
						else
						{
							_map[cx + 3][y] = MapContent(ContentType::WALL, GetAnima(ContentType::WALL));
							_map[cx - 3][y] = MapContent(ContentType::WALL, GetAnima(ContentType::WALL));
						}
						
						for (int x = -2; x < 3; x++)
						{
							_map[cx + x][y] = MapContent(ContentType::FLOOR, GetAnima(ContentType::FLOOR));
						}
					}
					for (int x = -2; x < 3; x++)
					{
						_map[cx + x][cy + w1 / 2 + 1] = MapContent(ContentType::AISLEWALL, GetAnima(ContentType::AISLEWALL));
						_map[cx + x][cy + INTERNAL - w2 / 2 - 1] = MapContent(ContentType::AISLEWALL, GetAnima(ContentType::AISLEWALL));
					}
				}
			}
		}
		/*for (int i = 0; i < MYMAPSIZE; i++)
		{
			for (int j = 0; j < MYMAPSIZE; j++)
			{

				ContentType a = _map[i][j].GetType();
				a = a;
			}
		}*/
	}

	void CGameMap::normalRoomGenerate(int i, int j)
	{
		int width = _Rooms[i][j]._width;
		int high = _Rooms[i][j]._high;
		int orgx = (ROOMINTERNAL >> 1) + ROOMINTERNAL * i - (width >> 1);
		int orgy = (ROOMINTERNAL >> 1) + ROOMINTERNAL * j - (high >> 1);
		int cx = _Rooms[i][j]._centerX;
		int cy = _Rooms[i][j]._centerY;

		// 隨機類型
		int type = rand() % 7;
		MapContent wall = MapContent(ContentType::WALL, GetAnima(ContentType::WALL, 1), true);
		//test type = 0;
		switch (type)
		{
		case 0:	// 空的
			break;
		case 1:	// 直線
			for (int x = 0; x < width - 4; x++)
			{
				_map[orgx + x][cy + 3] = wall;
				_map[orgx + x + 4][cy - 3] = wall;
			}
			break;
		case 2:	// 橫線
			for (int y = 0; y < high - 4; y++)
			{
				_map[cx + 3][orgy + y] = wall;
				_map[cx - 3][orgy + y + 4] = wall;
			}
			break;
		case 3: // 中間方形
			{
				int r = 3 + (rand() % 2);
				for (int x = -r; x <= r; x++)
					for (int y = -r; y <= r; y++)
					{
						_map[cx + x][cy + y] = wall;
					}
				break;
			}
		case 4:	// 中間叉叉
			{
				int r = 3 + (rand() % 2);
				for (int x = -r; x <= r; x++)
				{
					_map[cx + x][cy + x] = wall;
					_map[cx + x][cy - x] = wall;
				}
				break;
			}
		case 5:// 中間簡易愛心
			{
				int r = 4 + (rand() % 3);
				for (int y = -(r - 3); y <= 0; y++)
				{
					_map[cx - 3][cy + y] = wall;
					_map[cx + 3][cy + y] = wall;
				}
				for (int y = -(r - 2); y <= 1; y++)
				{
					_map[cx - 2][cy + y] = wall;
					_map[cx + 2][cy + y] = wall;
				}
				for (int y = -(r - 3); y <= 2; y++)
				{
					_map[cx - 1][cy + y] = wall;
					_map[cx + 1][cy + y] = wall;
				}
				for (int y = -(r - 4); y <= 3; y++)
					_map[cx][cy + y] = wall;

				break;
			}
		case 6:// 隨機矩形
			{
				int t = 2 + (rand() % 3);
				while(t--)
				{
					int rx = orgx + (3 + rand() % (width - 9)), ry = orgy + (3 + rand() % (high - 9));
					int w = 1 + (rand() % 4), h = 1;
					if (w > 1)
					{
						h = 1 + (rand() % 4);
					}
					for (int x = 0; x < w; x++)
					{
						for (int y = 0; y < h; y++)
						{
							_map[rx + x][ry + y] = wall;
						}
					}	
				}
				break;
			}
		default:
			break;
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

	bool CGameMap::IsContent(int x, int y, CGameMap::ContentType content)
	{
		x /= _MAPW;
		y /= _MAPH;
		if(x < 0 || y < 0 || x > MYMAPSIZE || y > MYMAPSIZE)
			GAME_ASSERT(false, "物件範圍超出地圖!");
		return _map[x][y].GetType() == content;
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

	vector<CAnimation>::iterator CGameMap::GetAnima(ContentType Type, int index)
	{
		// index < 0 隨機選擇
		if(index < 0)
			return _animas.at((int)Type).begin() + rand() % (int)_animas.at((int)Type).size();
		else 
			return _animas.at((int)Type).begin() + index;
		/*vector<CAnimation>::iterator iterator;
		
		switch (Type)
		{
		case game_framework::CGameMap::ContentType::NULLPTR:
			iterator = _animas.at(0).begin() + rand() % (int)_animas.at(0).size();
			break;
		case game_framework::CGameMap::ContentType::FLOOR:
			iterator = _animas.at(1).begin() + rand() % (int)_animas.at(1).size();
			break;
		case game_framework::CGameMap::ContentType::WALL:
			iterator = _animas.at(2).begin() + rand() % (int)_animas.at(2).size();
			break;
		case game_framework::CGameMap::ContentType::AISLEWALL:
			iterator = _animas.at(3).begin() + rand() % (int)_animas.at(3).size();
			break;
		default:
			ASSERT(0);
		}
		return iterator;*/
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
		_roomType = RoomData::RoomType::NOROOM;
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