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
		int _atk, _cost;		// 攻擊力、消耗能量

	private:
		void init();
	};
}
