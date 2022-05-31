#pragma once
#include "CGameWeapon.h"
#define RPS(X) GAME_ONE_SECONED / X

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	//	�}�ª���j
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
	//	��s����j
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