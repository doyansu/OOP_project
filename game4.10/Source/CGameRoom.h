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
		
		int GetX2();			// �k�U�a���I�y��
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
		int _maxEnemy, _reGenerate;			// �ͦ��ĤH�ơB���s�ͦ���
		int _generateDelay;					// ���s�ͦ����j
		bool _isStrat;						// ����i�J�ж��}�l�ͦ�
		RoomData _room;						// �ж���T�ͦ��a�Ϯɫغc
		vector<CEnemy*> _roomEnemys;		// �i�ѩж��޲z���Ǫ�
		vector<RoomWall*> _roomWalls;		// �q�D���j���󱱨�
		vector<CEnemy*> _enemys;			// �i�H�ͦ����Ǫ�����

	private:

	};
}