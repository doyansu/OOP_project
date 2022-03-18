#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CInitialPlayer.h"

namespace game_framework {

	CInitialPlayer::CInitialPlayer()
	{
		Initialize();
	}

	int CInitialPlayer::GetX2()
	{
		return _x + animation.Width();
	}

	int CInitialPlayer::GetY2()
	{
		return _y + animation.Height();
	}

	void CInitialPlayer::Initialize()
	{
		this->Reset();
		const int X_POS = 320;
		const int Y_POS = 200;
		_x = X_POS;
		_y = Y_POS;
	}

	void CInitialPlayer::LoadBitmap()
	{
		animation.AddBitmap(IDB_CH1_1, RGB(255, 255, 255));
		animation.AddBitmap(IDB_CH1_2, RGB(255, 255, 255));
		animation.AddBitmap(IDB_CH1_3, RGB(255, 255, 255));
		animation.AddBitmap(IDB_CH1_2, RGB(255, 255, 255));
		animation.SetDelayCount(500);
	}

	void CInitialPlayer::OnMove()
	{
		animation.OnMove();
		CGameObj::OnMove();
	}

	void CInitialPlayer::OnShow()
	{
		animation.SetTopLeft(_x, _y);
		animation.OnShow();
	}

}