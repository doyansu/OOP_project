#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameWeapons.h"
#include "CGameFactorys.h"


namespace game_framework {

	/////////////////////////////////////////////////////////////////////////////
	//	破舊的手槍
	CGameWeapon_Init& CGameWeapon_Init::Instance()
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

	CGameWeapon_Init::CGameWeapon_Init()
	{
		_spread = 5;
		_atk = 3;
		_shootDelay = RPS(3);
	}

	void CGameWeapon_Init::LoadBitmap()
	{
		_animaIter = GetAnima(CGameWeapon::Anima::Theta_0);
		_animaIter->AddBitmap(IDB_weapon_0_0, RGB(255, 255, 255));
		_animaIter = GetAnima(CGameWeapon::Anima::Theta_45);
		_animaIter->AddBitmap(IDB_weapon_0_45, RGB(255, 255, 255));
		_animaIter = GetAnima(CGameWeapon::Anima::Theta_90);
		_animaIter->AddBitmap(IDB_weapon_0_90, RGB(255, 255, 255));
		_animaIter = GetAnima(CGameWeapon::Anima::Theta_135);
		_animaIter->AddBitmap(IDB_weapon_0_135, RGB(255, 255, 255));
		_animaIter = GetAnima(CGameWeapon::Anima::Theta_180);
		_animaIter->AddBitmap(IDB_weapon_0_180, RGB(255, 255, 255));
		_animaIter = GetAnima(CGameWeapon::Anima::Theta_225);
		_animaIter->AddBitmap(IDB_weapon_0_225, RGB(255, 255, 255));
		_animaIter = GetAnima(CGameWeapon::Anima::Theta_270);
		_animaIter->AddBitmap(IDB_weapon_0_270, RGB(255, 255, 255));
		_animaIter = GetAnima(CGameWeapon::Anima::Theta_315);
		_animaIter->AddBitmap(IDB_weapon_0_315, RGB(255, 255, 255));

		*GetAnima(Anima::ARROW) = CGameArrow::Instance();

		_isLoad = true;
	}
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	//	嶄新的手槍

	CGameWeapon_NewInit& CGameWeapon_NewInit::Instance()
	{
		static CGameWeapon_NewInit Instance;
		static bool isLoad = false;
		if (isLoad == false)
		{
			Instance.LoadBitmap();
			isLoad = true;
		}
		return Instance;
	}

	CGameWeapon_NewInit::CGameWeapon_NewInit() :CGameWeapon()
	{
		_atk = 4;
		_cost = 0;
		_crit = 0;
		_spread = 7;
		_shootDelay = RPS(3);
		_weaponType = Type::NEWINIT;
	}

	void CGameWeapon_NewInit::LoadBitmap()
	{
		_animaIter = GetAnima(CGameWeapon::Anima::Theta_0);
		_animaIter->AddBitmap(IDB_weapon_1_0, RGB(255, 255, 255));
		_animaIter = GetAnima(CGameWeapon::Anima::Theta_45);
		_animaIter->AddBitmap(IDB_weapon_1_45, RGB(255, 255, 255));
		_animaIter = GetAnima(CGameWeapon::Anima::Theta_90);
		_animaIter->AddBitmap(IDB_weapon_1_90, RGB(255, 255, 255));
		_animaIter = GetAnima(CGameWeapon::Anima::Theta_135);
		_animaIter->AddBitmap(IDB_weapon_1_135, RGB(255, 255, 255));
		_animaIter = GetAnima(CGameWeapon::Anima::Theta_180);
		_animaIter->AddBitmap(IDB_weapon_1_180, RGB(255, 255, 255));
		_animaIter = GetAnima(CGameWeapon::Anima::Theta_225);
		_animaIter->AddBitmap(IDB_weapon_1_225, RGB(255, 255, 255));
		_animaIter = GetAnima(CGameWeapon::Anima::Theta_270);
		_animaIter->AddBitmap(IDB_weapon_1_270, RGB(255, 255, 255));
		_animaIter = GetAnima(CGameWeapon::Anima::Theta_315);
		_animaIter->AddBitmap(IDB_weapon_1_315, RGB(255, 255, 255));


		*GetAnima(Anima::ARROW) = CGameArrow::Instance();

		_isLoad = true;
	}

	void CGameWeapon_NewInit::Shoot(double x, double y)
	{
		if (_fire)
		{
			// 音效播放
			CAudio::Instance()->Play(_shootID);

			int t = 1;
			if (rand() % 5 == 0)	//	20 % 機率射出5發子彈
			{
				t = 5;
			}

			while (t--)
			{
				AddBullet(x, y, ProductFactory<CGameBullet>::Instance().GetProduct((int)CGameBullet::Type::INIT));
			}
			
			_fire = false;
			_fireCounter = _shootDelay;
		}
	}

	/////////////////////////////////////////////////////////////////////////////

}