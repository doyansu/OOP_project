#pragma once
#include "CGameObj.h"

namespace game_framework
{
	class CGameWeapon : public CGameObj
	{
	public:
		CGameWeapon();

	protected:
		int _atk, _cost;		// 攻擊力、消耗能量

	private:

	};
}
