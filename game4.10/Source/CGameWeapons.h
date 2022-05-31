#pragma once
#include "CGameWeapon.h"
#define RPS(X) GAME_ONE_SECONED / X

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	//	破舊的手槍
	class CGameWeapon_Init : public CGameWeapon
	{
	public:
		static CGameWeapon_Init& Instance();

		CGameWeapon_Init();
		void LoadBitmap();
	protected:
		
	private:
		
	};
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	//	嶄新的手槍
	class CGameWeapon_NewInit : public CGameWeapon
	{
	public:
		static CGameWeapon_NewInit& Instance();

		CGameWeapon_NewInit();
		void LoadBitmap();
		void Shoot(double x, double y);
	protected:

	private:

	};
	/////////////////////////////////////////////////////////////////////////////
}