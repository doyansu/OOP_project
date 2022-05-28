#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CUIWeapon.h"


namespace game_framework
{
	CUIWeapon::CUIWeapon()
	{
		_dy = _atk = _cost = _crit = _spread = 0;
		_moveDown = true;
	}

	void CUIWeapon::SetValue(int atk, int cost, int crit, int spread)
	{
		_atk = atk;
		_cost = cost;
		_crit = crit;
		_spread = spread;
	}

	void CUIWeapon::SetMove(bool moveDown)
	{
		_moveDown = moveDown;
	}

	void CUIWeapon::MoveUI()
	{
		// (this->Height() << 1) 為移動距離 (GAME_ONE_SECONED >> 3) 為 0.125 秒移動完成
		const int speed = (this->Height() << 1) / (GAME_ONE_SECONED >> 3);
		if (_moveDown)
		{
			_dy += speed;
		}
		else
		{
			_dy -= speed;
		}
		if (_dy > 0)
			_dy = 0;
		else if (_dy < -(this->Height() << 1))
			_dy = -(this->Height() << 1);
		_moveDown = true;
	}


	void CUIWeapon::ShowUI()
	{
		const int x = (SIZE_X - this->Width()) >> 1, y = SIZE_Y + _dy;
		this->SetTopLeft(x, y);
		this->OnShow();

		CInteger integer;
		integer.SetInteger(_atk);
		integer.SetTopLeft(x + 10 -integer.GetLen() * integer.GetWidth(), y);
		integer.ShowBitmap(false);
		integer.SetInteger(_cost);
		integer.SetTopLeft(x + 30 -integer.GetLen() * integer.GetWidth(), y);
		integer.ShowBitmap(false);
		integer.SetInteger(_crit);
		integer.SetTopLeft(x + 50 -integer.GetLen() * integer.GetWidth(), y);
		integer.ShowBitmap(false);
		integer.SetInteger(_spread);
		integer.SetTopLeft(x + 70 -integer.GetLen() * integer.GetWidth(), y);
		integer.ShowBitmap(false);
	}
}
