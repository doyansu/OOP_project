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
		init();
	}

	void CCharacter::init()
	{
		this->SetXY(300, 240);
		CAnimation run;
		_animas.push_back(run);
		_animaIter = _animas.begin();
	}

	void CCharacter::LoadBitmap()
	{
		_animas.at(0).AddBitmap(IDB_CH1_4, RGB(255, 255, 255));
		_animas.at(1).AddBitmap(IDB_CH1_0, RGB(255, 255, 255));
		_animas.at(1).AddBitmap(IDB_CH1_1, RGB(255, 255, 255));
		_animas.at(1).AddBitmap(IDB_CH1_2, RGB(255, 255, 255));
		_animas.at(1).AddBitmap(IDB_CH1_3, RGB(255, 255, 255));

	}

	void CCharacter::OnShow(CGameMap* map)
	{
		CGameObj::OnShow(map);
	}

	void CCharacter::OnMove()
	{
		if (_isMovingDown || _isMovingLeft || _isMovingRight || _isMovingUp)
			_animaIter = GetAnima(Anima::RUN);
		else
			_animaIter = GetAnima(Anima::INIT);

		CGameObj::OnMove();
	}

	vector<CAnimation>::iterator CCharacter::GetAnima(Anima type)
	{
		vector<CAnimation>::iterator anima = _animas.begin();
		switch (type)
		{
		case game_framework::CCharacter::Anima::INIT:
			anima = _animas.begin();
			break;
		case game_framework::CCharacter::Anima::RUN:
			anima = _animas.begin() + 1;
			break;
		default:
			break;
		}
		return anima;
	}
}