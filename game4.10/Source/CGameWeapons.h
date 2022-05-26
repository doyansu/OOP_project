#pragma once
#include "CGameWeapon.h"


namespace game_framework {

	class CGameWeapon_Init : public CGameWeapon
	{
	public:
		CGameWeapon_Init();
		void LoadBitmap();
	};

}