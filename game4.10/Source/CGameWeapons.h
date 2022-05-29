#pragma once
#include "CGameWeapon.h"
#define RPS 0

namespace game_framework {
	class CGameWeapon_Init : public CGameWeapon
	{
	public:
		static CGameWeapon_Init& Instance();

		CGameWeapon_Init();
		void LoadBitmap();
	protected:
		
	private:
		
	};

}