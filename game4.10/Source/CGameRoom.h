#pragma once
#include "CEnemy.h"
#include "CCharacter.h"
#include "CGameObjCenter.h"
#define REGENERATETIME GAME_ONE_SECONED >> 1

namespace game_framework
{
	class CGameTreasure : public CGameObj
	{
	public:
		enum class Anima { TREASURE, LEFTCOVER, RIGHTCOVER, TOP, ARROW, ANIMACOUNT };
		CGameTreasure()
		{
			const int AnimaSize = (int)Anima::ANIMACOUNT;
			_animas.clear();
			_animas.reserve(AnimaSize);
			for (int i = 0; i < AnimaSize; i++)
				_animas.push_back(CAnimation());

			_dtop = _dleft = _dright = 0;
			_collPlayer = false;
			this->SetTag("treasure");
		}

		int GetX2()
		{
			return _mx + GetAnima(Anima::TREASURE)->Width();
		}
		int GetY2()
		{
			return _my + GetAnima(Anima::TREASURE)->Height();
		}
		int Width()
		{
			return GetAnima(Anima::TREASURE)->Width();
		}
		int Height()
		{
			return GetAnima(Anima::TREASURE)->Height();
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
			_animaIter = GetAnima(Anima::ARROW);
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
		void OnObjCollision(CGameMap* map, CGameObj* other)
		{
			if (!_collPlayer && other->GetTag() == "player")
			{
				_collPlayer = true;
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
			if (_collPlayer)
			{
				GetAnima(Anima::ARROW)->OnMove();
				_collPlayer = false;
			}
			else // 重製動畫
			{
				GetAnima(Anima::ARROW)->Reset();
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

			if (_collPlayer && !_isDie)
			{
				_animaIter = GetAnima(Anima::ARROW);
				_animaIter->SetTopLeft(map->ScreenX(_mx + ((GetAnima(Anima::TREASURE)->Width() - _animaIter->Width()) >> 1)),
					map->ScreenY(_my - _animaIter->Height()));
				_animaIter->OnShow();
			}
		}

	protected:
		int _collPlayer;				//	碰到玩家
		int _dtop, _dleft, _dright;
	private:
		vector<CAnimation>::iterator GetAnima(Anima type)
		{
			return _animas.begin() + (int)type;
		}
	};
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

	class CGameRoom : public CGameObj
	{
	public:
		CGameRoom(RoomData*);
		~CGameRoom();
		
		int GetX2();			// 右下地圖點座標
		int GetY2();
		bool IsStrat();

		void OnMove(CGameMap*);
		void OnObjCollision(CGameMap*, CGameObj*);
		void OnDie(CGameMap*);
		void OnShow(CGameMap*);
		void Initialization(CGameMap*);

		static void Init()
		{
			clearTreasure.LoadBitmap();
			TransferGate.LoadBitmap();
			gameTreasure.LoadBitmap();
		}

		static CGameTransferGate* GetTransFerGate()
		{
			return &TransferGate;
		}

		// 間隔通道物件
		class RoomWall : public CGameObj
		{
		public:
			enum class Anima { START, PILLARSTART, PILLAREND, END, ANIMACOUNT};
			RoomWall()
			{
				// 動畫載入
				const int AnimaSize = (int)Anima::ANIMACOUNT;
				_animas.clear();
				_animas.reserve(AnimaSize);
				for (int i = 0; i < AnimaSize; i++)
					_animas.push_back(CAnimation());

				// 屬性設定
				this->SetTag("roomwall");
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
					// 開發中暫時拿掉
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
		void Die();

	private:
		class CGameClearTreasure : public CGameObj
		{
		public:
			enum class Anima { TREASURE, TREASUREDIE, LEFTCOVER, RIGHTCOVER, TOP, ANIMACOUNT };
			CGameClearTreasure()
			{
				const int AnimaSize = (int)Anima::ANIMACOUNT;
				_animas.clear();
				_animas.reserve(AnimaSize);
				for (int i = 0; i < AnimaSize; i++)
					_animas.push_back(CAnimation());

				_dtop = _dleft = _dright = 0;
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
				_animaIter->SetDelayCount(5);
				_animaIter->AddBitmap(IDB_TREASURE_0_0, RGB(255, 255, 255));
				_animaIter->AddBitmap(IDB_TREASURE_0_1, RGB(255, 255, 255));
				_animaIter->AddBitmap(IDB_TREASURE_0_2, RGB(255, 255, 255));
				_animaIter->AddBitmap(IDB_TREASURE_0_3, RGB(255, 255, 255));
				_animaIter->AddBitmap(IDB_TREASURE_0_2, RGB(255, 255, 255));
				_animaIter->AddBitmap(IDB_TREASURE_0_1, RGB(255, 255, 255));

				_animaIter = GetAnima(Anima::TREASUREDIE);
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
				GetAnima(Anima::TREASURE)->OnMove();
			}

			void OnShow(CGameMap* map)
			{
				if (_isDie)
				{
					_animaIter = GetAnima(Anima::TREASUREDIE);
					_animaIter->SetTopLeft(map->ScreenX(_mx), map->ScreenY(_my));
					_animaIter->OnShow();
				}
				else
				{
					_animaIter = GetAnima(Anima::TREASURE);
					_animaIter->SetTopLeft(map->ScreenX(_mx), map->ScreenY(_my));
					_animaIter->OnShow();
				}
				
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

		// 一般房間使用
		int _maxEnemy, _reGenerate;			// 生成敵人數、重新生成數
		int _generateDelay;					// 重新生成間隔
		bool _isStrat;						// 角色進入房間開始生成
		bool _hasEnemys;					// 擁有敵人物件需刪除
		RoomData* _room;					// 房間資訊生成地圖時建構
		vector<CEnemy*> _roomEnemys;		// 可由房間管理的怪物
		vector<RoomWall*> _roomWalls;		// 通道阻隔物件控制
		vector<CEnemy*> _enemys;			// 可以生成的怪物類型

		static CGameClearTreasure clearTreasure;	// 通關寶箱物件
		static CGameTransferGate TransferGate;		// 傳送門物件
		static CGameTreasure gameTreasure;			// 寶箱房間物件
	};

	





	
}