#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameRoom.h"

namespace game_framework 
{
	CAnimation CGameRoom::_marking;

	CGameRoom::CGameRoom(RoomData* data)
	{
		// �ݩʳ]�w
		_room = data;
		_mx = MYMAPWIDTH * (data->CenterX() - (data->Width() >> 1));
		_my = MYMAPHIGH * (data->CenterY() - (data->High() >> 1));
		_isStrat = false;
		_hasEnemys = true;
		this->SetShowPriority(2);

		// �}�o���վ�
		//_maxEnemy = 4 + (rand() % 3);
		//_reGenerate = 3 + (rand() % 3);
		_maxEnemy = 3;
		_reGenerate = 1;

		// �Ȯɳ]�w boss �ж�
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
		// �ھ������إߩж�
		switch (_room->GetRoomType())
		{
		case RoomData::RoomType::BOSS:		//	BOSS�ж�
		case RoomData::RoomType::NORMAL:	// �@��ж�
		{

			// �Ĥ@��Ǫ�
			int n = 1 + rand() % _maxEnemy;
			for (int i = 0; i < n; i++)
			{
				CEnemy* newEnemy = ProductFactory<CEnemy>::Instance().GetProduct(rand() % (int)CEnemy::Type::TYPECOUNT);//new CEnemy(*(_enemys.at(rand() % (int)_enemys.size())));
				// �I���ê���s���m
				do {
					newEnemy->SetXY(_mx + MYMAPWIDTH * (1 + rand() % (_room->Width() - 2)), _my + MYMAPHIGH * (1 + rand() % (_room->High() - 2)));
				} while (newEnemy->Collision(map));
				newEnemy->SetFree(false);
				_roomEnemys.push_back(newEnemy);
			}

			// �q�D��Ы�
			RoomWall wall;
			wall.LoadBitmap();
			wall.SetFree(false);
			int cx = _room->CenterX(), cy = _room->CenterY();
			int w = _room->Width(), h = _room->High();

			// �W�観�q�D
			if (_room->HasRoad(0))
			{
				wall.SetVector(0, 1);
				for (int x = -2; x < 3; x++)
				{
					wall.SetXY(MYMAPWIDTH * (cx + x), MYMAPHIGH * (cy - (h / 2) - 1));
					_roomWalls.push_back(new RoomWall(wall));
				}
			}
			// �U�観�q�D
			if (_room->HasRoad(1))
			{
				wall.SetVector(0, -1);
				for (int x = -2; x < 3; x++)
				{
					wall.SetXY(MYMAPWIDTH * (cx + x), MYMAPHIGH * (cy + (h / 2) + 1));
					RoomWall* newWall = new RoomWall(wall);								//	�U�誺����ܰ��󪱮a
					newWall->SetShowPriority(12);
					_roomWalls.push_back(newWall);
				}
			}
			// ���観�q�D
			if (_room->HasRoad(2))
			{
				wall.SetVector(1, 0);
				for (int y = -2; y < 3; y++)
				{
					wall.SetXY(MYMAPWIDTH * (cx - (w / 2) - 1), MYMAPHIGH * (cy + y));
					RoomWall* newWall = new RoomWall(wall);								
					newWall->SetShowPriority(y);			//	�վ��u���ץH���T���
					_roomWalls.push_back(newWall);
				}
			}
			// �k�観�q�D
			if (_room->HasRoad(3))
			{
				wall.SetVector(-1, 0);
				for (int y = -2; y < 3; y++)
				{
					wall.SetXY(MYMAPWIDTH * (cx + (w / 2) + 1), MYMAPHIGH * (cy + y));
					RoomWall* newWall = new RoomWall(wall);								
					newWall->SetShowPriority(y);			//	�վ��u���ץH���T���
					_roomWalls.push_back(newWall);
				}
			}
			break;
		}
		case RoomData::RoomType::END:		// �ǰe�ж�
		{
			CGameTransferGate::Instance()->SetXY(_room->CenterX() * MYMAPWIDTH - (CGameTransferGate::Instance()->Width() >> 1) + (MYMAPWIDTH >> 1),
				_room->CenterY() * MYMAPHIGH - (CGameTransferGate::Instance()->Height() >> 1) + (MYMAPHIGH >> 1));
			CGameObj::AddObj(CGameTransferGate::Instance());
			break;
		}
		case RoomData::RoomType::TREASURE:	//	�_�c�ж�
		{
			CGameTreasure* treasure = CGameTreasure::CreateObj(rand() % (int)CGameTreasure::Type::TYPECOUNT);
			treasure->SetXY(_room->CenterX() * MYMAPWIDTH - (treasure->Width() >> 1) + (MYMAPWIDTH >> 1),
				_room->CenterY() * MYMAPHIGH - (treasure->Height() >> 1) + (MYMAPHIGH >> 1));
			CGameObj::AddObj(treasure);
			break;
		}
		case RoomData::RoomType::SPECIAL:	//	�S��ж�
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
				if (!_marking.IsFinalBitmap())
					_marking.OnMove();

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

				// �ˬd�ж����Ǫ��O�_�w�g�������`
				for (CEnemy* obj : _roomEnemys)
				{
					if (obj->IsEnable())
					{
						if (obj->NeedFree())
							_generateDelay = REGENERATETIME;
						return;
					}

				}

				// �������`���s�ͦ�
				_roomEnemys.clear();
				_marking.Reset();
				if (_reGenerate > 0)
				{
					int r = 1 + (rand() % (_maxEnemy - 1));
					for (int i = 0; i < r; i++)
					{
						CEnemy* newEnemy = ProductFactory<CEnemy>::Instance().GetProduct(rand() % (int)CEnemy::Type::TYPECOUNT);;
						// �I���ê���s���m
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
			else
			{
				for (CEnemy* obj : _roomEnemys)
				{
					if(!obj->hasAppeared())
						obj->OnMove(map);
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
		// �o�䦳 bug �|�b���W��ܪ����٨S��X���D #�� �n���S�S���D�F ?.?

		switch (_room->GetRoomType())
		{
		case RoomData::RoomType::BOSS:
		case RoomData::RoomType::NORMAL:
		{
			const int w = (_marking.Width() >> 1);
			const int h = (_marking.Height() >> 1);
			for (CEnemy* obj : _roomEnemys)
			{
				if (!obj->NeedFree())
				{
					if (_isStrat && map->InScreen(obj->GetX1(), obj->GetY1(), obj->GetX2(), obj->GetY2()))
					{
						_marking.SetTopLeft(map->ScreenX(obj->CenterX() - w), map->ScreenY(obj->CenterY() - h));
						_marking.OnShow();
					}
					else if (map->InScreen(obj->GetX1(), obj->GetY1(), obj->GetX2(), obj->GetY2()))
						obj->OnShow(map);
				}
				
			}
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
			// ���a�Ĥ@���i�J�ж��Ǫ��}�l�ʧ@
			if (_isDie == false && _isStrat == false && other->GetTag() == "player")
			{
				// �����i�J�~�}�l
				int x1 = other->GetX1(), x2 = other->GetX2(), y1 = other->GetY1(), y2 = other->GetY2();
				if (this->GetX1() >= x1 || this->GetX2() <= x2 || this->GetY1() >= y1 || this->GetY2() <= y2)
					return;
				_isStrat = true;
				_hasEnemys = false;
				// �Ĥ@��Ǫ��}�l�ʧ@
				for (CEnemy* obj : _roomEnemys)
				{
					obj->SetFree(true);
					CGameObj::AddObj(obj);
				}
				// �q�D��}�l�ʧ@
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
		

		if (other->GetTag() == "player")		// �P�_���a�O�_�b�ж���
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

			CGameTreasure* treasure = CGameTreasure::CreateObj((int)CGameTreasure::Type::TYPECOUNT - 1);
			treasure->SetXY(_room->CenterX() * MYMAPWIDTH - (treasure->Width() >> 1) + (MYMAPWIDTH >> 1),
				_room->CenterY() * MYMAPHIGH + -(treasure->Height() >> 1) + CGameTransferGate::Instance()->Height() + (MYMAPHIGH >> 1));
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
			if (!_isStrat)	// ��_isStrat�ӧP�_�u���@�� _isStart �P OnMove �B OnObjCollision �������ˬd
				break;
			_isStrat = false;

			for (CGameObj* obj : _roomWalls)
			{
				obj->SetEnable(false);
				obj->SetDie(true);
			}
			_roomWalls.clear();

			CGameClearTreasure* cTreasure = CGameClearTreasure::CreateObj();
			// �I���ê���s���m
			do {
				cTreasure->SetXY(_mx + MYMAPWIDTH * (1 + rand() % (_room->Width() - 2)), _my + MYMAPHIGH * (1 + rand() % (_room->High() - 2)));
			} while (cTreasure->Collision(map));
			CGameObj::AddObj(cTreasure);
			
			break;
		}
		case RoomData::RoomType::BOSS:
		{
			if (!_isStrat || _generateDelay > 0)
			{
				_generateDelay--;
				break;
			}
			_isStrat = false;
			CGameTransferGate::Instance()->SetXY(_room->CenterX() * MYMAPWIDTH - (CGameTransferGate::Instance()->Width() >> 1) + (MYMAPWIDTH >> 1),
				_room->CenterY() * MYMAPHIGH - (CGameTransferGate::Instance()->Height() >> 1) + (MYMAPHIGH >> 1));
			CGameObj::AddObj(CGameTransferGate::Instance());
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





	// �ǰe������
	CGameTransferGate::CGameTransferGate()
	{
		this->SetFree(false);

		// �ʵe�]�w
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

		*GetAnima(CGameTransferGate::Anima::ARROW) = CGameArrow::Instance();
		
	}

	void CGameTransferGate::OnMove(CGameMap* map) 
	{
		GetAnima(CGameTransferGate::Anima::TransferGate)->OnMove();
		if (_isDie)
		{
			GetAnima(CGameTransferGate::Anima::ARROW)->OnMove();
			_isDie = false;
		}
		else // ���s�ʵe
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
			this->SetDie(true); // �ϥ� _isDie �ӧP�_�I��
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
