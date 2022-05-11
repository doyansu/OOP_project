#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameRoom.h"

namespace game_framework 
{
	CGameRoom::CGameClearTreasure CGameRoom::clearTreasure;
	CGameTransferGate CGameRoom::TransferGate;
	CGameTreasure CGameRoom::Treasure;
	CGameInteractOnceObj CGameRoom::potions[4];
	CGameTrackObj CGameRoom::TrackObj[2];

	CGameRoom::CGameRoom(RoomData* data)
	{
		// 屬性設定
		_room = data;
		_mx = MYMAPWIDTH * (data->CenterX() - (data->Width() >> 1));
		_my = MYMAPHIGH * (data->CenterY() - (data->High() >> 1));
		_isStrat = false;
		_hasEnemys = true;
		this->SetShowPriority(2);

		// 開發中調整
		//_maxEnemy = 4 + (rand() % 3);
		//_reGenerate = 3 + (rand() % 3);
		_maxEnemy = 2;
		_reGenerate = 1;

		// 暫時設定 boss 房間
		switch (data->GetRoomType())
		{
		case RoomData::RoomType::BOSS:
			_maxEnemy = 30;
			_reGenerate = 0;
			break;
		default:
			break;
		}

		_generateDelay = REGENERATETIME;
		_roomEnemys.reserve(_maxEnemy);
		_tag = "Room";

	}

	void CGameRoom::Initialization(CGameMap* map)
	{
		// 根據類型建立房間
		switch (_room->GetRoomType())
		{
		case RoomData::RoomType::BOSS:		//	BOSS房間
		case RoomData::RoomType::NORMAL:	// 一般房間
		{
			// 新增怪物
			CEnemy enemy;
			enemy.LoadBitmap();
			_enemys.reserve(10);
			_enemys.push_back(new CEnemy(enemy));


			// 第一批怪物
			for (int i = 0; i < _maxEnemy; i++)
			{
				CEnemy* newEnemy = new CEnemy(*(_enemys.at(rand() % (int)_enemys.size())));
				// 碰到障礙重新選位置
				do {
					newEnemy->SetXY(_mx + MYMAPWIDTH * (1 + rand() % (_room->Width() - 2)), _my + MYMAPHIGH * (1 + rand() % (_room->High() - 2)));
				} while (newEnemy->Collision(map));
				newEnemy->SetFree(false);
				_roomEnemys.push_back(newEnemy);
			}

			// 通道牆創建
			RoomWall wall;
			wall.LoadBitmap();
			wall.SetFree(false);
			int cx = _room->CenterX(), cy = _room->CenterY();
			int w = _room->Width(), h = _room->High();

			// 上方有通道
			if (_room->HasRoad(0))
			{
				wall.SetVector(0, 1);
				for (int x = -2; x < 3; x++)
				{
					wall.SetXY(MYMAPWIDTH * (cx + x), MYMAPHIGH * (cy - (h / 2) - 1));
					_roomWalls.push_back(new RoomWall(wall));
				}
			}
			// 下方有通道
			if (_room->HasRoad(1))
			{
				wall.SetVector(0, -1);
				for (int x = -2; x < 3; x++)
				{
					wall.SetXY(MYMAPWIDTH * (cx + x), MYMAPHIGH * (cy + (h / 2) + 1));
					RoomWall* newWall = new RoomWall(wall);								//	下方的需顯示高於玩家
					newWall->SetShowPriority(12);
					_roomWalls.push_back(newWall);
				}
			}
			// 左方有通道
			if (_room->HasRoad(2))
			{
				wall.SetVector(1, 0);
				for (int y = -2; y < 3; y++)
				{
					wall.SetXY(MYMAPWIDTH * (cx - (w / 2) - 1), MYMAPHIGH * (cy + y));
					RoomWall* newWall = new RoomWall(wall);								
					newWall->SetShowPriority(y);			//	調整優先度以正確顯示
					_roomWalls.push_back(newWall);
				}
			}
			// 右方有通道
			if (_room->HasRoad(3))
			{
				wall.SetVector(-1, 0);
				for (int y = -2; y < 3; y++)
				{
					wall.SetXY(MYMAPWIDTH * (cx + (w / 2) + 1), MYMAPHIGH * (cy + y));
					RoomWall* newWall = new RoomWall(wall);								
					newWall->SetShowPriority(y);			//	調整優先度以正確顯示
					_roomWalls.push_back(newWall);
				}
			}
			break;
		}
		case RoomData::RoomType::END:		// 傳送房間
		{
			TransferGate.SetXY(_room->CenterX() * MYMAPWIDTH - (TransferGate.Width() >> 1) + (MYMAPWIDTH >> 1),
				_room->CenterY() * MYMAPHIGH - (TransferGate.Height() >> 1) + (MYMAPHIGH >> 1));
			CGameObj::AddObj(&TransferGate);
			break;
		}
		case RoomData::RoomType::TREASURE:	//	寶箱房間
		{
			CGameTreasure* treasure = new CGameTreasure(Treasure);
			treasure->SetXY(_room->CenterX() * MYMAPWIDTH - (treasure->Width() >> 1) + (MYMAPWIDTH >> 1),
				_room->CenterY() * MYMAPHIGH - (treasure->Height() >> 1) + (MYMAPHIGH >> 1));
			CGameObj::AddObj(treasure);
			break;
		}
		case RoomData::RoomType::SPECIAL:	//	特殊房間
			break;
		default:
			break;
		}
	}

	CGameRoom::~CGameRoom()
	{
		switch (_room->GetRoomType())
		{
		case RoomData::RoomType::BOSS:
		case RoomData::RoomType::NORMAL:
		{
			if (_hasEnemys)
			{
				for (CEnemy* obj : _roomEnemys)
				{
					if (!obj->NeedFree())
						delete obj;
				}
			}
			for (RoomWall* obj : _roomWalls)
			{
				if (!obj->NeedFree())
					delete obj;
			}
			for (CEnemy* enemy : _enemys)
			{
				delete enemy;
			}
			break;
		}
		default:
			break;
		}
	}

	void CGameRoom::OnMove(CGameMap* map)
	{
		switch (_room->GetRoomType())
		{
		case RoomData::RoomType::BOSS:
		case RoomData::RoomType::NORMAL:
		{
			if (_isStrat)
			{
				if (_generateDelay > 0)
					_generateDelay--;
				else if (_generateDelay == 0)
				{
					_hasEnemys = false;
					for (CEnemy* obj : _roomEnemys)
					{
						obj->SetFree(true);
						CGameObj::AddObj(obj);
					}
				}

				// 檢查房間內怪物是否已經全部死亡
				for (CEnemy* obj : _roomEnemys)
				{
					if (obj->IsEnable())
					{
						if (obj->NeedFree())
							_generateDelay = REGENERATETIME;
						return;
					}

				}

				// 全部死亡重新生成
				_roomEnemys.clear();
				if (_reGenerate > 0)
				{
					int r = 1 + (rand() % (_maxEnemy - 1));
					for (int i = 0; i < r; i++)
					{
						CEnemy* newEnemy = new CEnemy(*(_enemys.at(rand() % (int)_enemys.size())));
						// 碰到障礙重新選位置
						do {
							newEnemy->SetXY(_mx + MYMAPWIDTH * (1 + rand() % (_room->Width() - 2)), _my + MYMAPHIGH * (1 + rand() % (_room->High() - 2)));
						} while (newEnemy->Collision(map));
						newEnemy->SetFree(false);
						_roomEnemys.push_back(newEnemy);
					}
					_reGenerate--;
				}
				else
				{
					this->Die();
				}
			}
			break;
		}
		default:
			break;
		}
		
	}

	void CGameRoom::OnShow(CGameMap* map)
	{
		// 這邊有 bug 會在左上顯示物件還沒找出問題 #更 好像又沒問題了 ?.?

		switch (_room->GetRoomType())
		{
		case RoomData::RoomType::BOSS:
		case RoomData::RoomType::NORMAL:
		{
			for (CEnemy* obj : _roomEnemys)
				if (!obj->NeedFree() && map->InScreen(obj->GetX1(), obj->GetY1(), obj->GetX2(), obj->GetY2()))
					obj->OnShow(map);
			break;
		}
		default:
			break;
		}
		
		
	}

	void CGameRoom::OnObjCollision(CGameMap* map, CGameObj* other)
	{
		switch (_room->GetRoomType())
		{
		case RoomData::RoomType::BOSS:
		case RoomData::RoomType::NORMAL:
		{
			// 玩家第一次進入房間怪物開始動作
			if (_isDie == false && _isStrat == false && other->GetTag() == "player")
			{
				// 完全進入才開始
				int x1 = other->GetX1(), x2 = other->GetX2(), y1 = other->GetY1(), y2 = other->GetY2();
				if (this->GetX1() >= x1 || this->GetX2() <= x2 || this->GetY1() >= y1 || this->GetY2() <= y2)
					return;
				_isStrat = true;
				_hasEnemys = false;
				// 第一批怪物開始動作
				for (CEnemy* obj : _roomEnemys)
				{
					obj->SetFree(true);
					CGameObj::AddObj(obj);
				}
				// 通道牆開始動作
				for (RoomWall* obj : _roomWalls)
				{
					obj->SetFree(true);
					CGameObj::AddObj(obj);
				}

			}
			break;
		}
		default:
			break;
		}
		

		if (other->GetTag() == "player")		// 判斷玩家是否在房間內
		{
			int x1 = other->GetX1(), x2 = other->GetX2(), y1 = other->GetY1(), y2 = other->GetY2();
			if (this->GetX1() >= x1 || this->GetX2() <= x2 || this->GetY1() >= y1 || this->GetY2() <= y2)
			{
				_room->SetPlayerIn(false);
			}
			else
			{
				_room->SetExplored(true);
				_room->SetPlayerIn(true);
			}
		}
			
	}

	void CGameRoom::Die() 
	{
		this->SetEnable(false);
		this->SetDie(true);

		switch (_room->GetRoomType())
		{
		case RoomData::RoomType::BOSS:
		{
			_generateDelay = GAME_ONE_SECONED << 1;
			for (CGameObj* obj : _roomWalls)
			{
				obj->SetEnable(false);
				obj->SetDie(true);
			}
			_roomWalls.clear();

			CGameTreasure* treasure = new CGameTreasure(Treasure);
			treasure->SetXY(_room->CenterX() * MYMAPWIDTH - (treasure->Width() >> 1) + (MYMAPWIDTH >> 1),
				_room->CenterY() * MYMAPHIGH + -(treasure->Height() >> 1) + TransferGate.Height() + (MYMAPHIGH >> 1));
			CGameObj::AddObj(treasure);
			break;
		}
		default:
			break;
		}
	}

	void CGameRoom::OnDie(CGameMap* map)
	{
		switch (_room->GetRoomType())
		{
		case RoomData::RoomType::NORMAL:
		{
			if (!_isStrat)	// 用_isStrat來判斷只做一次 _isStart 與 OnMove 、 OnObjCollision 有關需檢查
				break;
			_isStrat = false;

			for (CGameObj* obj : _roomWalls)
			{
				obj->SetEnable(false);
				obj->SetDie(true);
			}
			_roomWalls.clear();

			CGameClearTreasure* cTreasure = new CGameClearTreasure(clearTreasure);
			// 碰到障礙重新選位置
			do {
				cTreasure->SetXY(_mx + MYMAPWIDTH * (1 + rand() % (_room->Width() - 2)), _my + MYMAPHIGH * (1 + rand() % (_room->High() - 2)));
			} while (cTreasure->Collision(map));
			CGameObj::AddObj(cTreasure);
			
			break;
		}
		case RoomData::RoomType::BOSS:
		{
			if (_isStrat && _generateDelay-- > 0)	// 用_isStrat來判斷只做一次 _isStart 與 OnMove 、 OnObjCollision 有關需檢查
				break;
			_isStrat = false;
			
			TransferGate.SetXY(_room->CenterX() * MYMAPWIDTH - (TransferGate.Width() >> 1) + (MYMAPWIDTH >> 1),
				_room->CenterY() * MYMAPHIGH - (TransferGate.Height() >> 1) + (MYMAPHIGH >> 1));
			CGameObj::AddObj(&TransferGate);
			break;
		}
		default:
			break;
		}
	}
	
	int CGameRoom::GetX2()
	{
		return _mx + MYMAPWIDTH * _room->Width();
	}

	int CGameRoom::GetY2()
	{
		return _my + MYMAPHIGH * _room->High();
	}

	bool CGameRoom::IsStrat()
	{
		return _isStrat;
	}





	// 傳送門物件
	CGameTransferGate::CGameTransferGate()
	{
		this->SetFree(false);

		// 動畫設定
		const int AnimaSize = 2;
		_animas.clear();
		CAnimation animation;
		for (int i = 0; i < AnimaSize; i++)
			_animas.push_back(CAnimation(animation));
	}

	void CGameTransferGate::LoadBitmap() 
	{
		_animaIter = GetAnima(CGameTransferGate::Anima::TransferGate);
		_animaIter->SetDelayCount(2);
		_animaIter->AddBitmap(IDB_TransferGate_0, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_TransferGate_1, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_TransferGate_2, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_TransferGate_3, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_TransferGate_4, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_TransferGate_5, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_TransferGate_6, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_TransferGate_7, RGB(255, 255, 255));

		_animaIter = GetAnima(CGameTransferGate::Anima::ARROW);
		_animaIter->SetDelayCount(2);
		_animaIter->AddBitmap(IDB_ItemArrow_0, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_ItemArrow_1, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_ItemArrow_2, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_ItemArrow_3, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_ItemArrow_4, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_ItemArrow_5, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_ItemArrow_4, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_ItemArrow_3, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_ItemArrow_2, RGB(0, 0, 0));
		_animaIter->AddBitmap(IDB_ItemArrow_1, RGB(0, 0, 0));
	
		
	}

	void CGameTransferGate::OnMove(CGameMap* map) 
	{
		GetAnima(CGameTransferGate::Anima::TransferGate)->OnMove();
		if (_isDie)
		{
			GetAnima(CGameTransferGate::Anima::ARROW)->OnMove();
			_isDie = false;
		}
		else // 重製動畫
		{
			GetAnima(CGameTransferGate::Anima::ARROW)->Reset();
		}
	}

	void CGameTransferGate::OnShow(CGameMap* map) 
	{
		_animaIter = GetAnima(CGameTransferGate::Anima::TransferGate);
		_animaIter->SetTopLeft(map->ScreenX(_mx), map->ScreenY(_my));
		_animaIter->OnShow();
		if (_isDie)
		{
			_animaIter = GetAnima(CGameTransferGate::Anima::ARROW);
			_animaIter->SetTopLeft(map->ScreenX(_mx + ((GetAnima(CGameTransferGate::Anima::TransferGate)->Width() - _animaIter->Width()) >> 1)), map->ScreenY(_my));
			_animaIter->OnShow();
		}
	}

	void CGameTransferGate::OnObjCollision(CGameMap* map, CGameObj* other) 
	{
		if (other->GetTag() == "player")
		{
			this->SetDie(true); // 使用 _isDie 來判斷碰撞
		}
	}

	int CGameTransferGate::GetX2() 
	{
		return _mx + GetAnima(CGameTransferGate::Anima::TransferGate)->Width();
	}

	int CGameTransferGate::GetY2() 
	{
		return _my + GetAnima(CGameTransferGate::Anima::TransferGate)->Height();
	}

	int CGameTransferGate::Width()
	{
		return GetAnima(CGameTransferGate::Anima::TransferGate)->Width();
	}

	int CGameTransferGate::Height()
	{
		return GetAnima(CGameTransferGate::Anima::TransferGate)->Height();
	}

	vector<CAnimation>::iterator CGameTransferGate::GetAnima(CGameTransferGate::Anima type)
	{
		return _animas.begin() + (int)type;
	}
	
}
