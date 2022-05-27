#pragma once
#include "CGameWeapon.h"
#include "CGameFactorys.h"


namespace game_framework {

	class CGameWeapon_Init : public CGameWeapon
	{
	public:
		static CGameWeapon_Init& Instance()
		{
			static CGameWeapon_Init Instance;
			static bool isLoad = false;
			if (isLoad == false)
			{
				Instance.LoadBitmap();
				isLoad = true;
			}
			return Instance;
		}

		CGameWeapon_Init();
		void LoadBitmap();
	protected:
		
	private:
		
	};

}