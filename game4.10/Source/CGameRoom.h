#pragma once
#include "CEnemy.h"
#include "CCharacter.h"
#include "CGameObjCenter.h"
#define REGENERATETIME GAME_CYCLE_TIME >> 1

namespace game_framework
{
	class CGameRoom : public CGameObj
	{
	public:
		CGameRoom(RoomData);
		~CGameRoom();
		
		int GetX2();			// 右下地圖點座標
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

		class RoomWall : public CGameObj
		{
		public:
			RoomWall();
			void LoadBitmap();
			void OnMove(CGameMap*);
			void OnObjCollision(CGameMap*, CGameObj*);
			void OnDie(CGameMap*);
		protected:
		private:
		};

	protected:
		int _maxEnemy, _reGenerate;			// 生成敵人數、重新生成數
		int _generateDelay;					// 重新生成間隔
		bool _isStrat;						// 角色進入房間開始生成
		bool _hasEnemys;					// 擁有敵人物件需刪除
		RoomData _room;						// 房間資訊生成地圖時建構
		vector<CEnemy*> _roomEnemys;		// 可由房間管理的怪物
		vector<RoomWall*> _roomWalls;		// 通道阻隔物件控制
		vector<CEnemy*> _enemys;			// 可以生成的怪物類型

	private:
		class ClearTreasure : public CGameObj
		{
		public:
			enum class Anima { TREASURE, LEFTCOVER, RIGHTCOVER };
			ClearTreasure()
			{
				const int AnimaSize = 3;
				_animas.clear();
				_animas.reserve(AnimaSize);
				for (int i = 0; i < AnimaSize; i++)
					_animas.push_back(CAnimation());
			}
			void LoadBitmap()
			{
				_animaIter = GetAnima(Anima::TREASURE);
				_animaIter->AddBitmap(IDB_TREASURE_0_0, RGB(255, 255, 255));
			}
			void OnObjCollision(CGameMap* map, CGameObj* other)
			{
				if (other->GetTag() == "player")
				{
				}
			}
			void OnDie(CGameMap* map)
			{
				_animaIter->OnMove();
			}
		protected:
		private:
			vector<CAnimation>::iterator GetAnima(Anima type)
			{
				return _animas.begin() + (int)type;
			}
		};
		static ClearTreasure clearTreasure;
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
}