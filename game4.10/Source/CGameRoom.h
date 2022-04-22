#pragma once
#include "CEnemy.h"
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
		void OnDie();
		void OnShow(CGameMap*);
		void Initialization(CGameMap*);

		class RoomWall : public CGameObj
		{
		public:
			RoomWall();
			void LoadBitmap();
			void OnMove(CGameMap*);
			void OnObjCollision(CGameMap*, CGameObj*);
			void OnDie();
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

	};


	class CGameTransferGate : public CGameObj
	{
	public:
		enum class Anima { ARROW, TransferGate };
		CGameTransferGate()
		{
			this->SetFree(false);

			// 動畫設定
			const int AnimaSize = 2;
			_animas.clear();
			CAnimation animation;
			//animation.SetDelayCount(3);
			for (int i = 0; i < AnimaSize; i++)
				_animas.push_back(CAnimation(animation));
		}

		void LoadBitmap()
		{
			_animaIter = GetAnima(CGameTransferGate::Anima::TransferGate);
			_animaIter->AddBitmap(IDB_TransferGate_0, RGB(255, 255, 255));

			_animaIter = GetAnima(CGameTransferGate::Anima::ARROW);
			_animaIter->AddBitmap(IDB_0, RGB(0, 0, 0));
			_animaIter->AddBitmap(IDB_1, RGB(0, 0, 0));
			_animaIter->AddBitmap(IDB_2, RGB(0, 0, 0));
			_animaIter->AddBitmap(IDB_3, RGB(0, 0, 0));
		}

		void OnMove(CGameMap* map)
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

		void OnShow(CGameMap* map)
		{
			_animaIter = GetAnima(CGameTransferGate::Anima::TransferGate);
			_animaIter->SetTopLeft(map->ScreenX(_mx), map->ScreenY(_my));
			_animaIter->OnShow();
			if (_isDie)
			{
				_animaIter = GetAnima(CGameTransferGate::Anima::ARROW);
				_animaIter->SetTopLeft(map->ScreenX(_mx), map->ScreenY(_my));
				_animaIter->OnShow();
			}
		}

		void OnObjCollision(CGameMap* map, CGameObj* other)
		{
			if (other->GetTag() == "player")
			{
				this->SetDie(true); // 使用 _isDie 來判斷碰撞
			}
		}

		int GetX2()
		{
			return _mx + GetAnima(CGameTransferGate::Anima::TransferGate)->Width();
		}

		int GetY2()
		{
			return _mx + GetAnima(CGameTransferGate::Anima::TransferGate)->Height();
		}

		int Width()
		{
			return GetAnima(CGameTransferGate::Anima::TransferGate)->Width();
		}

		int Height()
		{
			return GetAnima(CGameTransferGate::Anima::TransferGate)->Height();
		}

	protected:

	private:
		vector<CAnimation>::iterator GetAnima(CGameTransferGate::Anima type)
		{
			return _animas.begin() + (int)type;
		}
	};
}