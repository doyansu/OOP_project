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
		//	屬性設定
		_sx = _sy = 0;
		_px = _py = MYORGROOM;	// 中心設定在起始房間

		//	動畫設定
		_animas.reserve((int)Anima::ANIMACOUNT);
		for (int i = 0; i < (int)Anima::ANIMACOUNT; i++)
		{
			_animas.push_back(CAnimation());
		}
	}

	void CUIMinMap::SetRoom(RoomData ** rooms)
	{
		_rooms = rooms;
	}

	void CUIMinMap::OnMove()
	{
		if (_rooms == nullptr)
			return;
	}

	void CUIMinMap::OnShow()
	{
		if (_rooms == nullptr)
			return;

		// 從起始房間開始顯示
		queue<Point> queue;
		vector<CAnimation>::iterator p;
		Point start = Point(MYORGROOM, MYORGROOM);	//	 從起點開始
		start.SetParent(new Point(start));
		queue.push(start);
		int dir[4][2] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };	// 搜索用向量
		while (!queue.empty())
		{
			Point point = queue.front();
			int x = point.Get(0), y = point.Get(1);
			RoomData room = _rooms[x][y];

			if (room.IsExplored())		//	探索過
			{
				if (room.PlayerIn())		//	玩家在房間內
				{
					_px = point.Get(0);
					_py = point.Get(1);
				}
				else
				{
					p = GetAnima(Anima::EXPLORED);
					p->SetTopLeft(_sx + x * MYMAPWIDTH, _sy + y * MYMAPHIGH);
					p->OnShow();
				}

				// 加入下一點
				for (int i = 0; i < 4; i++)
				{
					if (room.HasRoad(i))
					{
						int nx = x + dir[i][0], ny = y + +dir[i][1];
						Point newPoint(nx, ny);
						if (newPoint != *(point.GetParent()))		// 不回到上一點
						{
							newPoint.SetParent(new Point(point));
							queue.push(newPoint);

							//	顯示通道
							switch (i)
							{
							case 0:	//	上
								p = GetAnima(Anima::AILSES);
								p->SetTopLeft(_sx + x * MYMAPWIDTH + 7, _sy + y * MYMAPHIGH - 8);
								p->OnShow();
								break;
							case 1:	//	下
								p = GetAnima(Anima::AILSES);
								p->SetTopLeft(_sx + x * MYMAPWIDTH + 7, _sy + y * MYMAPHIGH + 17);
								p->OnShow();
								break;
							case 2:	//	左
								p = GetAnima(Anima::AILSEH);
								p->SetTopLeft(_sx + x * MYMAPWIDTH - 8, _sy + y * MYMAPHIGH + 7);
								p->OnShow();
								break;
							case 3:	//	右
								p = GetAnima(Anima::AILSEH);
								p->SetTopLeft(_sx + x * MYMAPWIDTH + 17, _sy + y * MYMAPHIGH + 7);
								p->OnShow();
								break;
							default:
								break;
							}
						}
					}
				}
			}
			else
			{
				p = GetAnima(Anima::NOTEXPLORED);
				p->SetTopLeft(_sx + x * MYMAPWIDTH, _sy + y * MYMAPHIGH);
				p->OnShow();
			}

			// 顯示玩家位置
			if (point == Point(_px, _py))
			{
				p = GetAnima(Anima::PLAYERIN);
				p->SetTopLeft(_sx + _px * MYMAPWIDTH, _sy + _py * MYMAPHIGH);
				p->OnShow();
			}

			// 顯示房間圖片
			switch (room.GetRoomType())
			{
			case RoomData::RoomType::INIT:
				p = GetAnima(Anima::INIT);
				p->SetTopLeft(_sx + x * MYMAPWIDTH, _sy + y * MYMAPHIGH);
				p->OnShow();
				break;
			case RoomData::RoomType::TREASURE:
				p = GetAnima(Anima::TREASURE);
				p->SetTopLeft(_sx + x * MYMAPWIDTH, _sy + y * MYMAPHIGH);
				p->OnShow();
				break;
			case RoomData::RoomType::END:
				p = GetAnima(Anima::END);
				p->SetTopLeft(_sx + x * MYMAPWIDTH, _sy + y * MYMAPHIGH);
				p->OnShow();
				break;
			case RoomData::RoomType::BOSS:	// 暫無圖片
				break;
			default:
				break;
			}

			delete point.GetParent();
			queue.pop();
		}
		
		/*vector<CAnimation>::iterator p;
		p = GetAnima(Anima::END);
		p->SetTopLeft(_sx, _sy);
		p->OnShow();*/
	}

	void CUIMinMap::LoadBitmap()
	{
		vector<CAnimation>::iterator p;
		p = GetAnima(Anima::NOTEXPLORED);
		p->AddBitmap(IDB_MinMap_NOTEXPLORED, RGB(255, 255, 255));
		p = GetAnima(Anima::EXPLORED);
		p->AddBitmap(IDB_MinMap_EXPLORED, RGB(255, 255, 255));
		p = GetAnima(Anima::PLAYERIN);
		p->AddBitmap(IDB_MinMap_Playerin, RGB(0, 0, 0));
		p = GetAnima(Anima::INIT);
		p->AddBitmap(IDB_MinMap_INIT, RGB(255, 255, 255));
		p = GetAnima(Anima::TREASURE);
		p->AddBitmap(IDB_MinMap_TREASURE, RGB(255, 255, 255));
		p = GetAnima(Anima::END);
		p->AddBitmap(IDB_MinMap_END, RGB(255, 255, 255));
		p = GetAnima(Anima::BOSS);
		p->AddBitmap(IDB_MinMap_END, RGB(255, 255, 255));
		p = GetAnima(Anima::AILSES);
		p->AddBitmap(IDB_MinMap_AILSES, RGB(255, 255, 255));
		p = GetAnima(Anima::AILSEH);
		p->AddBitmap(IDB_MinMap_AILSEH, RGB(255, 255, 255));
	}

	void CUIMinMap::SetXY(int x, int y)
	{
		_sx = x;
		_sy = y;
	}

	void CUIMinMap::PlayerIn(int x, int y)
	{
		_px = x;
		_py = y;
	}

	vector<CAnimation>::iterator CUIMinMap::GetAnima(Anima type)
	{
		return _animas.begin() + (int)type;
	}

	
}