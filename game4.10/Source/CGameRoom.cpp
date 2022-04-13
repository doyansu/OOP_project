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
		// �ݩʳ]�w
		_room = data;
		_mx = MYMAPWIDTH * (data.CenterX() - (data.Width() >> 1));
		_my = MYMAPHIGH * (data.CenterY() - (data.High() >> 1));
		_isStrat = false;
		_maxEnemy = 4 + (rand() % 3);
		//_reGenerate = 3 + (rand() % 3);
		_reGenerate = 1;
		_generateDelay = 60;
		_roomEnemys.reserve(_maxEnemy);
		_tag = "Room";

		

	}

	void CGameRoom::Initialization(CGameMap* map)
	{
		// �s�W�Ǫ�
		CEnemy enemy;
		enemy.LoadBitmap();
		_enemys.reserve(10);
		_enemys.push_back(new CEnemy(enemy));

		// �Ĥ@��Ǫ�
		for (int i = 0; i < _maxEnemy; i++)
		{
			CEnemy* newEnemy = new CEnemy(*(_enemys.at(rand() % (int)_enemys.size())));
			// �I���ê���s���m
			do {
				newEnemy->SetXY(_mx + MYMAPWIDTH * (1 + rand() % (_room.Width() - 2)), _my + MYMAPHIGH * (1 + rand() % (_room.High() - 2)));
			} while (newEnemy->Collision(map));
			newEnemy->SetFree(false);
			_roomEnemys.push_back(newEnemy);
		}

		// �q�D��Ы�
		RoomWall wall;
		wall.LoadBitmap();
		wall.SetFree(false);
		int cx = _room.CenterX(), cy = _room.CenterY();
		int w = _room.Width(), h = _room.High();

		// �W�観�q�D
		if (_room.HasRoad(0))
		{
			wall.SetVector(0, 1);
			for (int x = -2; x < 3; x++)
			{
				wall.SetXY(MYMAPWIDTH * (cx + x), MYMAPHIGH * (cy - (h / 2) - 1));
				_roomWalls.push_back(new RoomWall(wall));
			}
		}
		// �U�観�q�D
		if (_room.HasRoad(1))
		{
			wall.SetVector(0, -1);
			for (int x = -2; x < 3; x++)
			{
				wall.SetXY(MYMAPWIDTH * (cx + x), MYMAPHIGH * (cy + (h / 2) + 1));
				_roomWalls.push_back(new RoomWall(wall));
			}
		}
		// ���観�q�D
		if (_room.HasRoad(2))
		{
			wall.SetVector(1, 0);
			for (int y = -2; y < 3; y++)
			{
				wall.SetXY(MYMAPWIDTH * (cx - (w / 2) - 1), MYMAPHIGH * (cy + y));
				_roomWalls.push_back(new RoomWall(wall));
			}
		}
		// �k�観�q�D
		if (_room.HasRoad(3))
		{
			wall.SetVector(-1, 0);
			for (int y = -2; y < 3; y++)
			{
				wall.SetXY(MYMAPWIDTH * (cx + (w / 2) + 1), MYMAPHIGH * (cy + y));
				_roomWalls.push_back(new RoomWall(wall));
			}
		}
	}

	CGameRoom::~CGameRoom()
	{
		for (CEnemy* obj : _roomEnemys)
		{
			if (!obj->NeedFree())
				delete obj;
		}
		for (CEnemy* enemy : _enemys)
		{
			delete enemy;
		}
		for (RoomWall* obj : _roomWalls)
		{
			if (!obj->NeedFree())
				delete obj;
		}
			
	}

	void CGameRoom::OnMove(CGameMap* map)
	{
		if (_isStrat)
		{
			if (_generateDelay > 0)
				_generateDelay--;
			else if (_generateDelay == 0)
			{
				for (CEnemy* obj : _roomEnemys)
				{
					obj->SetFree(true);
					CGameObjCenter::AddObj(obj);
				}	
			}

			// �ˬd�ж����Ǫ��O�_�w�g�������`
			for (CEnemy* obj : _roomEnemys)
			{
				if (obj->IsEnable())
				{
					if(obj->NeedFree())
						_generateDelay = 60;
					return;
				}
					
			}

			// �������`���s�ͦ�
			if (_reGenerate > 0)
			{
				_roomEnemys.clear();
				int r = 1 + (rand() % (_maxEnemy - 1));
				for (int i = 0; i < r; i++)
				{
					CEnemy* newEnemy = new CEnemy(*(_enemys.at(rand() % (int)_enemys.size())));
					// �I���ê���s���m
					do {
						newEnemy->SetXY(_mx + MYMAPWIDTH * (1 + rand() % (_room.Width() - 2)), _my + MYMAPHIGH * (1 + rand() % (_room.High() - 2)));
					} while (newEnemy->Collision(map));
					newEnemy->SetFree(false);
					_roomEnemys.push_back(newEnemy);
				}
				_reGenerate--;
			}
			else if(_reGenerate <= 0)
			{
				_roomEnemys.clear();
				this->SetEnable(false);
				this->SetDie(true);
			}
		}
	}

	void CGameRoom::OnShow(CGameMap* map)
	{
		// �o�䦳 bug �|�b���W��ܪ����٨S��X���D #�� �n���S�S���D�F ?.?
		for (CEnemy* obj : _roomEnemys)
			if(!obj->NeedFree() && map->InScreen(obj->GetX1(), obj->GetY1(), obj->GetX2(), obj->GetY2()))
				obj->OnShow(map);
		//
		
	}

	void CGameRoom::OnObjCollision(CGameMap* map, CGameObj* other)
	{
		// ���a�i�J�ж��Ǫ��}�l�ʧ@
		if (_isStrat == false && other->GetTag() == "player")
		{
			// �����i�J�~�}�l
			int x1 = other->GetX1(), x2 = other->GetX2(), y1 = other->GetY1(), y2 = other->GetY2();
			if (this->GetX1() >= x1 || this->GetX2() <= x2 || this->GetY1() >= y1 || this->GetY2() <= y2)
				return;
			_isStrat = true;	
			// �Ĥ@��Ǫ��}�l�ʧ@
			for (CEnemy* obj : _roomEnemys)
			{
				obj->SetFree(true);
				CGameObjCenter::AddObj(obj);
			}
			// �q�D��}�l�ʧ@
			for (RoomWall* obj : _roomWalls)
			{
				obj->SetFree(true);
				CGameObjCenter::AddObj(obj);
			}

		}
			
	}

	void CGameRoom::OnDie() 
	{
		for (CGameObj* obj : _roomWalls)
		{
			obj->SetEnable(false);
			obj->SetDie(true);
		}
		this->SetDie(false);
	}
	
	int CGameRoom::GetX2()
	{
		return _mx + MYMAPWIDTH * _room.Width();
	}

	int CGameRoom::GetY2()
	{
		return _my + MYMAPHIGH * _room.High();
	}

	// ���j�q�D����
	CGameRoom::RoomWall::RoomWall()
	{
		// �ʵe���J
		const int AnimaSize = 2;
		_animas.clear();
		_animas.reserve(AnimaSize);
		for (int i = 0; i < AnimaSize; i++)
			_animas.push_back(CAnimation());

		// �ݩʳ]�w
		this->SetTag("roomwall");
	}

	void CGameRoom::RoomWall::LoadBitmap()
	{
		_animaIter = _animas.begin();
		_animaIter->AddBitmap(IDB_Wall1, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_Wall2, RGB(255, 255, 255));

		_animaIter = _animas.begin() + 1;
		_animaIter->AddBitmap(IDB_Wall2, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_Wall1, RGB(255, 255, 255));
		_animaIter->AddBitmap(IDB_Wall0, RGB(255, 255, 255));
	}

	void CGameRoom::RoomWall::OnMove(CGameMap* map)
	{
		if(!_animaIter->IsFinalBitmap())
			_animaIter->OnMove();
	}

	void CGameRoom::RoomWall::OnDie()
	{
		_animaIter = _animas.begin() + 1;
		if (!_animaIter->IsFinalBitmap())
			_animaIter->OnMove();
		else
			this->SetDie(false);
	}

	void CGameRoom::RoomWall::OnObjCollision(CGameMap* map, CGameObj* other)
	{
		if (other->GetTag() == "player")
		{
			// �}�o���Ȯɮ���
			/*int dx = (int)_vector[0] * other->GetMoveSpeed();
			int dy = (int)_vector[1] * other->GetMoveSpeed();
			other->SetXY(other->GetX1() + dx, other->GetY1() + dy);*/
		}
		else if (other->GetTag() == "enemy")
		{
			int dx = (int)other->GetVectorX();
			int dy = (int)other->GetVectorY();
			other->SetXY(other->GetX1() - dx, other->GetY1() - dy);
		}
	}

	
}
