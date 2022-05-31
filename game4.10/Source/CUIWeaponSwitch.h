#pragma once
#include "CUIButton.h"
#include "CGameWeapon.h"

namespace game_framework
{
	class CUIWeaponSwitch : public CUIButton
	{
	public:
		static CUIWeaponSwitch& Instance()
		{
			static CUIWeaponSwitch instance;
			static bool isLoad = false;
			if (isLoad == false)
			{
				instance.AddBitmap(IDB_weapon_ui_switch, RGB(255, 255, 255));
				isLoad = true;
			}
			return instance;
		}

		void ShowUI();
		void SetWeapon(CGameWeapon*);

	protected:


	private:
		CGameWeapon* _weapon;
		CUIWeaponSwitch();
		CUIWeaponSwitch(const CUIWeaponSwitch&);
	};
}
