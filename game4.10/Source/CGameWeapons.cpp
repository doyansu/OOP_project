#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameWeapons.h"

namespace game_framework {

	CGameWeapon_Init::CGameWeapon_Init():CGameWeapon()
	{
		_spread = 5;
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

		_bullet->LoadBitmap();

		*GetAnima(Anima::ARROW) = CGameArrow::Instance();

		_isLoad = true;
	}

}