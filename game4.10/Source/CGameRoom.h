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
		
		int GetX2();			// �k�U�a���I�y��
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
		int _maxEnemy, _reGenerate;			// �ͦ��ĤH�ơB���s�ͦ���
		int _generateDelay;					// ���s�ͦ����j
		bool _isStrat;						// ����i�J�ж��}�l�ͦ�
		bool _hasEnemys;					// �֦��ĤH����ݧR��
		RoomData _room;						// �ж���T�ͦ��a�Ϯɫغc
		vector<CEnemy*> _roomEnemys;		// �i�ѩж��޲z���Ǫ�
		vector<RoomWall*> _roomWalls;		// �q�D���j���󱱨�
		vector<CEnemy*> _enemys;			// �i�H�ͦ����Ǫ�����

	private:

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
		void OnDie() {};

		int GetX2();
		int GetY2();
		int Width();
		int Height();

	protected:

	private:
		vector<CAnimation>::iterator GetAnima(CGameTransferGate::Anima type);
	};
}