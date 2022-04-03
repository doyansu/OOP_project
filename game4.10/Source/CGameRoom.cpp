#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameRoom.h"

namespace game_framework 
{
	CGameRoom::CGameRoom(RoomData data)
	{
		// 屬性設定
		_room = data;
		_mx = MYMAPWIDTH * (data.CenterX() - (data.Width() >> 1));
		_my = MYMAPHIGH * (data.CenterY() - (data.High() >> 1));
		_isStrat = false;
		_maxEnemy = 5;
		_reGenerate = 3;
		_roomObjs.reserve(_maxEnemy);

		// 新增怪物
		CEnemy enemy;
		enemy.LoadBitmap();
		_enemys.reserve(10);
		_enemys.push_back(enemy);
		
		// 第一批怪物
		for (int i = 0; i < _maxEnemy; i++)
		{
			CEnemy* newEnemy = new CEnemy(_enemys.at(rand() % (int)_enemys.size()));
			newEnemy->SetXY(_mx + MYMAPWIDTH * (2 + rand() % (_room.Width() - 4)), _my + MYMAPHIGH * (2 + rand() % (_room.High() - 4)));
			newEnemy->SetFree(false);
			_roomObjs.push_back(newEnemy);
		}
			
	}

	CGameRoom::~CGameRoom()
	{
		for (CGameObj* obj : _roomObjs)
		{
			if (!obj->NeedFree())
				delete obj;
		}
			
	}

	void CGameRoom::OnMove(CGameMap* map)
	{
		if (_isStrat)
		{
			for (CGameObj* obj : _roomObjs)
			{
				if (obj->IsEnable())
					return;
			}
			if (_reGenerate > 0)
			{
				_roomObjs.clear();
				int r = 1 + (rand() % (_maxEnemy - 1));
				for (int i = 0; i < r; i++)
				{
					CEnemy* newEnemy = new CEnemy(_enemys.at(rand() % (int)_enemys.size()));
					newEnemy->SetXY(_mx + MYMAPWIDTH * (2 + rand() % (_room.Width() - 4)), _my + MYMAPHIGH * (2 + rand() % (_room.High() - 4)));
					_roomObjs.push_back(newEnemy);
					CGameObjCenter::AddObj(newEnemy);
				}
				_reGenerate--;
			}
		}
	}

	void CGameRoom::OnShow(CGameMap* map)
	{
		if (!_isStrat)
		{
			for (CGameObj* obj : _roomObjs)
				obj->OnShow(map);
		}
	}

	void CGameRoom::OnObjCollision(CGameObj* other)
	{
		// 玩家進入房間怪物開始動作
		if (other->GetTag() == "player" && _isStrat == false)
		{
			_isStrat = true;				
			for (CGameObj* obj : _roomObjs)
			{
				obj->SetFree(true);
				CGameObjCenter::AddObj(obj);
			}
		}
			
	}

	void CGameRoom::OnDie() 
	{

	}
	
	int CGameRoom::GetX2()
	{
		return _mx + MYMAPWIDTH * _room.Width();
	}

	int CGameRoom::GetY2()
	{
		return _my + MYMAPHIGH * _room.High();
	}

	
}
