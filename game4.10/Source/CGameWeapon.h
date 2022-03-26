#pragma once
#include "CGameObj.h"

namespace game_framework
{
	class CGameWeapon : public CGameObj
	{
	public:
		CGameWeapon();

		void LoadBitmap();
		void OnMove(CGameMap* map);
		//void OnShow(CGameMap* map);
		void ObjFuntion(CGameObj*);
		void Reset();

	protected:
		int _atk, _cost;		// �����O�B���ӯ�q
		CGameObj bullet;

	private:
		void init();
	};
}
