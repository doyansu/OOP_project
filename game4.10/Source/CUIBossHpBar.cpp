#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CUIBossHpBar.h"

namespace game_framework
{
	CUIBossHpBar::CUIBossHpBar()
	{
		_enable = false;
		_percent = 100;
	}

	void CUIBossHpBar::SetPercent(int value)
	{
		if (value >= 0 && value <= 100)
		{
			_percent = value;
		}
	}

	void CUIBossHpBar::SetEnable(bool enable)
	{
		this->_enable = enable;
	}

	void CUIBossHpBar::LoadBitmap()
	{
		this->AddBitmap(IDB_BossHpBar_backGround);
		_fill.AddBitmap(IDB_BossHpBar_fill);
	}

	void CUIBossHpBar::ShowHpBar()
	{
		if (_enable)
		{
			this->OnShow();
			int t = (this->Width() - 20) * _percent / 100;
			for (int i = 0; i < t; i++)
			{
				_fill.SetTopLeft(this->Left() + 10 + i, this->Top() + 5);
				_fill.OnShow();
			}
		}
	}
}