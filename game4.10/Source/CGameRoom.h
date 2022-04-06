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

	protected:
		int _maxEnemy, _reGenerate;			//�ͦ��ĤH�ơB���s�ͦ���
		int _generateDelay;
		bool _isStrat;
		RoomData _room;
		vector<CGameObj*> _roomObjs;
		vector<CEnemy*> _enemys;

	private:

	};
}