#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CCharacter.h"

namespace game_framework {
	CCharacter::CCharacter()
	{
		this->SetXY(300, 240);
	}

	int CCharacter::GetX2()
	{
		return _x + animation.Width();
	}

	int CCharacter::GetY2()
	{
		return _y + animation.Height();
	}

	void CCharacter::LoadBitmap()
	{
		animation.AddBitmap(IDB_CH1_0, RGB(255, 255, 255));
		animation.AddBitmap(IDB_CH1_1, RGB(255, 255, 255));
		animation.AddBitmap(IDB_CH1_2, RGB(255, 255, 255));
		animation.AddBitmap(IDB_CH1_3, RGB(255, 255, 255));
		animation.SetDelayCount(5);
	}

	void CCharacter::OnShow()
	{
		animation.SetTopLeft(_x, _y);
		animation.OnShow();
		animation.OnMove();
	}
}