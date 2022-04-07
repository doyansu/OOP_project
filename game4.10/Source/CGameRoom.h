#pragma once
#include "CEnemy.h"
#include "CGameObjCenter.h"

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
		void OnObjCollision(CGameObj*);
		void OnDie();
		void OnShow(CGameMap*);

		class RoomWall : public CGameObj
		{
		public:
			RoomWall();
			void LoadBitmap();
			void OnMove(CGameMap*);
			void OnObjCollision(CGameObj*);
			void OnDie();
		protected:
		private:
		};

	protected:
		int _maxEnemy, _reGenerate;			// 生成敵人數、重新生成數
		int _generateDelay;					// 重新生成間隔
		bool _isStrat;						// 角色進入房間開始生成
		RoomData _room;						// 房間資訊生成地圖時建構
		vector<CEnemy*> _roomEnemys;		// 可由房間管理的怪物
		vector<RoomWall*> _roomWalls;		// 通道阻隔物件控制
		vector<CEnemy*> _enemys;			// 可以生成的怪物類型

	private:

	};
}