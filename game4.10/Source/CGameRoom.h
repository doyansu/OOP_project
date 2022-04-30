#pragma once
#include "CEnemy.h"
#include "CCharacter.h"
#include "CGameObjCenter.h"
#define REGENERATETIME GAME_ONE_SECONED >> 1

namespace game_framework
{
	class CGameRoom : public CGameObj
	{
	public:
		CGameRoom(RoomData);
		~CGameRoom();
		
		int GetX2();			// �k�U�a���I�y��
		int GetY2();
		void OnMove(CGameMap*);
		void OnObjCollision(CGameMap*, CGameObj*);
		void OnDie(CGameMap*);
		void OnShow(CGameMap*);
		void Initialization(CGameMap*);

		static void Init()
		{
			clearTreasure.LoadBitmap();
		}

		// ���j�q�D����
		class RoomWall : public CGameObj
		{
		public:
			enum class Anima { START, PILLARSTART, PILLAREND, END };
			RoomWall()
			{
				// �ʵe���J
				const int AnimaSize = 4;
				_animas.clear();
				_animas.reserve(AnimaSize);
				for (int i = 0; i < AnimaSize; i++)
					_animas.push_back(CAnimation());

				// �ݩʳ]�w
				this->SetTag("roomwall");
				this->SetShowPriority(12);
				_dtop = 0;
			}
			void LoadBitmap()
			{
				_animaIter = GetAnima(Anima::START);
				_animaIter->SetDelayCount(3);
				_animaIter->AddBitmap(IDB_Wall2, RGB(255, 255, 255));
				_animaIter->AddBitmap(IDB_Wall1, RGB(255, 255, 255));

				_animaIter = GetAnima(Anima::PILLARSTART);
				_animaIter->SetDelayCount(1);
				_animaIter->AddBitmap(IDB_AISLEWALL_PILLAR_5, RGB(255, 255, 255));
				_animaIter->AddBitmap(IDB_AISLEWALL_PILLAR_4, RGB(255, 255, 255));
				_animaIter->AddBitmap(IDB_AISLEWALL_PILLAR_3, RGB(255, 255, 255));
				_animaIter->AddBitmap(IDB_AISLEWALL_PILLAR_2, RGB(255, 255, 255));
				_animaIter->AddBitmap(IDB_AISLEWALL_PILLAR_1, RGB(255, 255, 255));
				_animaIter->AddBitmap(IDB_AISLEWALL_PILLAR_0, RGB(255, 255, 255));

				_animaIter = GetAnima(Anima::PILLAREND);
				_animaIter->SetDelayCount(1);
				_animaIter->AddBitmap(IDB_AISLEWALL_PILLAR_0, RGB(255, 255, 255));
				_animaIter->AddBitmap(IDB_AISLEWALL_PILLAR_1, RGB(255, 255, 255));
				_animaIter->AddBitmap(IDB_AISLEWALL_PILLAR_2, RGB(255, 255, 255));
				_animaIter->AddBitmap(IDB_AISLEWALL_PILLAR_3, RGB(255, 255, 255));
				_animaIter->AddBitmap(IDB_AISLEWALL_PILLAR_4, RGB(255, 255, 255));
				_animaIter->AddBitmap(IDB_AISLEWALL_PILLAR_5, RGB(255, 255, 255));

				_animaIter = GetAnima(Anima::END);
				_animaIter->SetDelayCount(3);
				_animaIter->AddBitmap(IDB_Wall1, RGB(255, 255, 255));
				_animaIter->AddBitmap(IDB_Wall2, RGB(255, 255, 255));
				_animaIter->AddBitmap(IDB_AISLEWALL_0, RGB(255, 255, 255));
			}
			void OnMove(CGameMap*)
			{
				if (_dtop > -25)
				{
					_dtop -= 5;
					if (!GetAnima(Anima::PILLARSTART)->IsFinalBitmap())
						GetAnima(Anima::PILLARSTART)->OnMove();
				}
				else if (!GetAnima(Anima::START)->IsFinalBitmap())
					GetAnima(Anima::START)->OnMove();
			}
			void OnShow(CGameMap* map)
			{
				if (this->_isEnable)
				{
					_animaIter = GetAnima(Anima::START);
					_animaIter->SetTopLeft(map->ScreenX(_mx), map->ScreenY(_my + _dtop));
					_animaIter->OnShow();
					_animaIter = GetAnima(Anima::PILLARSTART);
					_animaIter->SetTopLeft(map->ScreenX(_mx), map->ScreenY(_my + 25 + _dtop));
					_animaIter->OnShow();
				}
				else
				{
					_animaIter = GetAnima(Anima::END);
					_animaIter->SetTopLeft(map->ScreenX(_mx), map->ScreenY(_my + _dtop));
					_animaIter->OnShow();
					_animaIter = GetAnima(Anima::PILLAREND);
					_animaIter->SetTopLeft(map->ScreenX(_mx), map->ScreenY(_my + 25 + _dtop));
					_animaIter->OnShow();
				}	
				
			}
			void OnObjCollision(CGameMap*, CGameObj* other)
			{
				if (other->GetTag() == "player")
				{
					// �}�o���Ȯɮ���
					while (this->Collision(other))
					{
						other->SetXY(other->GetX1() + (int)_vector[0], other->GetY1() + (int)_vector[1]);
					}
				}
			}
			void OnDie(CGameMap*)
			{
				if (_dtop < 0)
				{
					_dtop += 5;
					if(!GetAnima(Anima::PILLAREND)->IsFinalBitmap())
						GetAnima(Anima::PILLAREND)->OnMove();
				}
				else if (!GetAnima(Anima::END)->IsFinalBitmap())
					GetAnima(Anima::END)->OnMove();
				else
					this->SetDie(false);
			}
		protected:
			int _dtop;
		private:
			vector<CAnimation>::iterator GetAnima(Anima type)
			{
				return _animas.begin() + (int)type;
			}
		};

	protected:
		int _maxEnemy, _reGenerate;			// �ͦ��ĤH�ơB���s�ͦ���
		int _generateDelay;					// ���s�ͦ����j
		bool _isStrat;						// ����i�J�ж��}�l�ͦ�
		bool _hasEnemys;					// �֦��ĤH����ݧR��
		RoomData _room;						// �ж���T�ͦ��a�Ϯɫغc
		vector<CEnemy*> _roomEnemys;		// �i�ѩж��޲z���Ǫ�
		vector<RoomWall*> _roomWalls;		// �q�D���j���󱱨�
		vector<CEnemy*> _enemys;			// �i�H�ͦ����Ǫ�����

	private:
		class ClearTreasure : public CGameObj
		{
		public:
			enum class Anima { TREASURE, LEFTCOVER, RIGHTCOVER, TOP };
			ClearTreasure()
			{
				const int AnimaSize = 4;
				_animas.clear();
				_animas.reserve(AnimaSize);
				for (int i = 0; i < AnimaSize; i++)
					_animas.push_back(CAnimation());

				_dtop, _dleft, _dright = 0;
				this->SetTag("cleartreasure");
			}

			int GetX2()
			{
				return _mx + GetAnima(Anima::TREASURE)->Width();
			}
			int GetY2()
			{
				return _my + GetAnima(Anima::TREASURE)->Height();
			}
			void LoadBitmap()
			{
				_animaIter = GetAnima(Anima::TREASURE);
				_animaIter->AddBitmap(IDB_TREASURE_0_0, RGB(255, 255, 255));
				_animaIter = GetAnima(Anima::TOP);
				_animaIter->AddBitmap(IDB_TREASURE_0_top, RGB(255, 255, 255));
				_animaIter = GetAnima(Anima::LEFTCOVER);
				_animaIter->AddBitmap(IDB_TREASURE_0_left, RGB(255, 255, 255));
				_animaIter = GetAnima(Anima::RIGHTCOVER);
				_animaIter->AddBitmap(IDB_TREASURE_0_right, RGB(255, 255, 255));
			}
			void OnObjCollision(CGameMap* map, CGameObj* other)
			{
				if (other->GetTag() == "player")
				{
				}
			}
			void OnDie(CGameMap* map) 
			{
				if (_dleft == -20 && _dright == 20 && _dtop > -4)
					_dtop--;
				if (_dleft > -20)
					_dleft--;
				if (_dright < 20)
					_dright++;
			}
			void OnMove(CGameMap* map)
			{
				for (CAnimation anima : _animas)
				{
					anima.OnMove();
				}
			}
			void OnShow(CGameMap* map)
			{
				_animaIter = GetAnima(Anima::TREASURE);
				_animaIter->SetTopLeft(map->ScreenX(_mx), map->ScreenY(_my));
				_animaIter->OnShow();
				_animaIter = GetAnima(Anima::TOP);
				_animaIter->SetTopLeft(map->ScreenX(_mx + 1), map->ScreenY(_my + _dtop));
				_animaIter->OnShow();
				_animaIter = GetAnima(Anima::LEFTCOVER);
				_animaIter->SetTopLeft(map->ScreenX(_mx + 2 + _dleft), map->ScreenY(_my + _dtop));
				_animaIter->OnShow();
				_animaIter = GetAnima(Anima::RIGHTCOVER);
				_animaIter->SetTopLeft(map->ScreenX(_mx + 20 + _dright), map->ScreenY(_my + _dtop));
				_animaIter->OnShow();
			}

		protected:
			int _dtop, _dleft, _dright;
		private:
			vector<CAnimation>::iterator GetAnima(Anima type)
			{
				return _animas.begin() + (int)type;
			}
		};

		static ClearTreasure clearTreasure;
	};

	/*class ClearTreasure : public CGameObj
	{
	public:
		enum class Anima { TREASURE, LEFTCOVER, RIGHTCOVER, TOP };
		ClearTreasure()
		{
			const int AnimaSize = 4;
			_animas.clear();
			_animas.reserve(AnimaSize);
			for (int i = 0; i < AnimaSize; i++)
				_animas.push_back(CAnimation());

			_dtop, _dleft, _dright = 0;
			this->SetTag("cleartreasure");
		}

		int GetX2()
		{
			return _mx + GetAnima(Anima::TREASURE)->Width();
		}
		int GetY2()
		{
			return _my + GetAnima(Anima::TREASURE)->Height();
		}
		void LoadBitmap()
		{
			_animaIter = GetAnima(Anima::TREASURE);
			_animaIter->AddBitmap(IDB_TREASURE_0_0, RGB(255, 255, 255));
			_animaIter = GetAnima(Anima::TOP);
			_animaIter->AddBitmap(IDB_TREASURE_0_top, RGB(255, 255, 255));
			_animaIter = GetAnima(Anima::LEFTCOVER);
			_animaIter->AddBitmap(IDB_TREASURE_0_left, RGB(255, 255, 255));
			_animaIter = GetAnima(Anima::RIGHTCOVER);
			_animaIter->AddBitmap(IDB_TREASURE_0_right, RGB(255, 255, 255));
		}
		void OnObjCollision(CGameMap* map, CGameObj* other)
		{
			if (other->GetTag() == "player")
			{
			}
		}
		void OnDie(CGameMap* map)
		{
			if (_dleft == -20 && _dright == 20 && _dtop > -4)
				_dtop--;
			if (_dleft > -20)
				_dleft--;
			if (_dright < 20)
				_dright++;
		}
		void OnMove(CGameMap* map)
		{
			for (CAnimation anima : _animas)
			{
				anima.OnMove();
			}
		}
		void OnShow(CGameMap* map)
		{
			_animaIter = GetAnima(Anima::TREASURE);
			_animaIter->SetTopLeft(map->ScreenX(_mx), map->ScreenY(_my));
			_animaIter->OnShow();
			_animaIter = GetAnima(Anima::TOP);
			_animaIter->SetTopLeft(map->ScreenX(_mx + 1), map->ScreenY(_my + _dtop));
			_animaIter->OnShow();
			_animaIter = GetAnima(Anima::LEFTCOVER);
			_animaIter->SetTopLeft(map->ScreenX(_mx + 2 + _dleft), map->ScreenY(_my + _dtop));
			_animaIter->OnShow();
			_animaIter = GetAnima(Anima::RIGHTCOVER);
			_animaIter->SetTopLeft(map->ScreenX(_mx + 20 + _dright), map->ScreenY(_my + _dtop));
			_animaIter->OnShow();
		}

	protected:
		int _dtop, _dleft, _dright;
	private:
		vector<CAnimation>::iterator GetAnima(Anima type)
		{
			return _animas.begin() + (int)type;
		}
	};*/





	class CGameTransferGate : public CGameObj
	{
	public:
		enum class Anima { ARROW, TransferGate };
		CGameTransferGate();

		void LoadBitmap();
		void OnMove(CGameMap* map);
		void OnShow(CGameMap* map);
		void OnObjCollision(CGameMap* map, CGameObj* other);

		int GetX2();
		int GetY2();
		int Width();
		int Height();

	protected:

	private:
		vector<CAnimation>::iterator GetAnima(CGameTransferGate::Anima type);
	};
}