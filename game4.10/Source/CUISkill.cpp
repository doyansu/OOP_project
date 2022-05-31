#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CUISkill.h"

namespace game_framework
{
	CUISkill::CUISkill()
	{
		_percent = 100;
	}

	void CUISkill::SetValue(int percent)
	{
		if(percent <= 100 && percent >= 0)
			_percent = percent;
	}

	void CUISkill::ShowUI()
	{
		const int x = this->Left(), y = this->Top();

		_backGround.SetTopLeft(x + ((this->Width() - _backGround.Width()) >> 1), y + 18);
		_backGround.OnShow();

		CAnimation* color = &_white;
		if (_percent == 100)
			color = &_blue;

		const int y2 = y + this->Height() - 22;		//	從下往上顯示的起點
		const int percent = _percent * 60 / 100;	//	100 % 分成 60 塊
		for (int i = 0; i < percent; i++)
		{
			color->SetTopLeft(x + ((this->Width() - color->Width()) >> 1), y2 - i);
			color->OnShow();
		}

		this->OnShow();
	}

	void CUISkill::LoadBitmap()
	{
		this->AddBitmap(IDB_Skill_UI, RGB(255, 255, 255));
		_white.AddBitmap(IDB_Skill_UI_white, RGB(255, 255, 255));
		_blue.AddBitmap(IDB_Skill_UI_blue, RGB(255, 255, 255));
		_backGround.AddBitmap(IDB_Skill_UI_backGround, RGB(255, 255, 255));
	}

}