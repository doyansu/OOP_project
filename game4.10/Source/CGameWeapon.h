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
		void Reset();

	protected:
		int _atk, _cost;		// �����O�B���ӯ�q

	private:
		void init();
	};
}
