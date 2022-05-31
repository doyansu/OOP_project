#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameDmgInteger.h"

namespace game_framework
{
	CGameDmgInteger::CGameDmgInteger()
	{
		_surviveTime = 0;
		_survive = GAME_ONE_SECONED >> 2;
		this->SetColor(CInteger::Color::RED);
	}

	void CGameDmgInteger::AddDmg(int dmg)
	{
		this->Add(dmg);
		_surviveTime = _survive;
	}

	void CGameDmgInteger::OnShow()
	{
		if (_surviveTime > 0)
		{
			_surviveTime--;
			this->ShowBitmap(false);
		}
		else
			this->SetInteger(0);
	}

	bool CGameDmgInteger::IsSurvive()
	{
		return _surviveTime > 0;
	}

	void CGameDmgInteger::SetSurviveTime(int value)
	{
		if (value > 0)
			_survive = value;
	}
}