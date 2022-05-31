#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CUIWeaponSwitch.h"

namespace game_framework
{
	CUIWeaponSwitch::CUIWeaponSwitch()
	{
		_weapon = nullptr;
	}

	void CUIWeaponSwitch::SetWeapon(CGameWeapon* weapon)
	{
		_weapon = weapon;
	}

	void CUIWeaponSwitch::ShowUI()
	{
		this->OnShow();

		if (_weapon != nullptr)
		{
			const int x = this->Left(), y = this->Top();
			CInteger integer;
			CInteger::LoadBitmap();

			integer.SetInteger(_weapon->GetCost());
			integer.SetTopLeft(x + 10, y + 5);
			integer.ShowBitmap(false);

			vector<CAnimation>::iterator it = _weapon->GetAnima(CGameWeapon::Anima::Theta_0);
			it->SetTopLeft(x + 25, y + 25);
			it->OnShow();
		}
	}
}